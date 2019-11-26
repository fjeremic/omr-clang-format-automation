#!/bin/bash
###############################################################################
# Copyright (c) 2017, 2018 IBM Corp. and others
#
# This program and the accompanying materials are made available under
# the terms of the Eclipse Public License 2.0 which accompanies this
# distribution and is available at https://www.eclipse.org/legal/epl-2.0/
# or the Apache License, Version 2.0 which accompanies this distribution and
# is available at https://www.apache.org/licenses/LICENSE-2.0.
#           
# This Source Code may also be made available under the following
# Secondary Licenses when the conditions for such availability set
# forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
# General Public License, version 2 with the GNU Classpath
# Exception [1] and GNU General Public License, version 2 with the
# OpenJDK Assembly Exception [2].
# 
# [1] https://www.gnu.org/software/classpath/license.html
# [2] http://openjdk.java.net/legal/assembly-exception.html
#                       
# SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
###############################################################################

print_help () {
  echo ""
}

check_clang_format_exists () {
  if ! type clang-format-9 > /dev/null 2>&1; then
    echo "Error: Could not find clang-format-9"
    exit 1
  fi
}

check_clang_format_version () {
  local CLANG_FORMAT_VERSION=`clang-format-9 --version`
  
  if [ "$CLANG_FORMAT_VERSION" != "clang-format version 9.0.0-2 (tags/RELEASE_900/final)" ]; then
    echo "Error: Incorrect clang-format version installed:"
    echo "    Installed:"
    echo "        $CLANG_FORMAT_VERSION"
    echo "    "
    echo "    Expected:"
    echo "        clang-format version 9.0.0-2 (tags/RELEASE_900/final)"
    exit 1
  fi
}

check_git_toplevel () {
  local GIT_TOPLEVEL=`git rev-parse --show-toplevel 2>&1`

  if [ "$PWD" != "$GIT_TOPLEVEL" ]; then
    echo "Error: You must be at the git repository root directory to run this command"
    echo "    Current directory:"
    echo "        $PWD"
    echo "    "
    echo "    Repository root directory:"
    echo "        $GIT_TOPLEVEL"
    exit 1
  fi
}

check_git_commit () {
  if ! git cat-file -e $1 > /dev/null 2>&1; then
    echo "Error: $1 is not a valid commit in this local repository"
    exit 1
  fi
}

check_git_ancestor () {
  local GIT_MERGE_BASE=`git merge-base $1 $2 2>&1`

  if [ "$1" != "$GIT_MERGE_BASE" ]; then
    echo "Error: $1 is not a direct ancestor of $2"
    exit 1
  fi
}

check_git_diff () {
  echo "  Checking for diff..."

  local DIFF=`git ls-files --modified`
  if [[ $DIFF ]]; then
    echo "  Error in formatting encountered"
    echo "  Generating patch file to correct formatting for $1"
    git diff > clang-format-$1.patch
    echo "  clang-format-$1.patch:"
    echo "==============================================================================="
    cat clang-format-$1.patch
    echo "==============================================================================="
    exit 1
  else
    echo "  Formatting check complete on $COMMIT"
  fi  
}

check_format () {
  local COMMIT_TO_CHECK_AGAINST=$1

  check_clang_format_exists
  check_clang_format_version
  check_git_toplevel

  local COMMITS=`git rev-list --reverse HEAD ^$COMMIT_TO_CHECK_AGAINST`
  if [[ $COMMITS ]]; then
    for COMMIT in $COMMITS; do
      echo "Checking out commit $COMMIT"
      git checkout --quiet $COMMIT
      echo "  Formatting $COMMIT"

      local FILES_CHANGED=`git diff HEAD~ --name-only`
      for FILE in $FILES_CHANGED; do
        if test -f "$FILE"; then
          if echo "$FILE" | grep -E "\.(cpp|cc|hpp|c|h)$" > /dev/null 2>&1; then
            echo "    Formatting $FILE"
            clang-format-9 -style=file -i "$FILE"
          fi
        fi
      done

      check_git_diff $COMMIT
      echo
    done
  else
    echo "Running formatting on entire repository"
    find . -regex '.*\.\(cpp\|cc\|hpp\|c\|h\)' -exec clang-format-9 -style=file -i {} \;

    check_git_diff "master"
    echo
  fi

  echo "Formatting check complete"
}

reformat_branch () {
  local COMMIT_BEFORE_FORMAT=$1
  local COMMIT_AFTER_FORMAT=$2

  check_clang_format_exists
  check_clang_format_version
  check_git_toplevel

  if ! git symbolic-ref --quiet HEAD > /dev/null 2>&1; then
    echo "Error: Cannot proceed because repository is in a detached HEAD state"
    exit 1
  fi

  if ! git diff --quiet > /dev/null 2>&1; then
    echo "Error: Cannot proceed because working tree has uncommited changes"
    exit 1
  fi

  echo "Validate the commit before formatting is valid"
  check_git_commit $COMMIT_BEFORE_FORMAT

  echo "Validate the commit after formatting is valid"
  check_git_commit $COMMIT_AFTER_FORMAT

  echo "Validate the commit before formatting is a direct ancestor of the commit after formatting"
  check_git_ancestor $COMMIT_BEFORE_FORMAT $COMMIT_AFTER_FORMAT

  echo "Validate the HEAD is rebased on the commit before formatting"
  check_git_ancestor $COMMIT_BEFORE_FORMAT "HEAD"

  OLD_BRANCH="`git rev-parse --abbrev-ref HEAD`"
  NEW_BRANCH="$OLD_BRANCH-formatted"

  echo "Validate new branch ($NEW_BRANCH) for formatting does not exist"
  if git rev-parse --verify $NEW_BRANCH > /dev/null 2>&1; then
    echo "Error: $NEW_BRANCH already exists"
    exit 1
  fi

  echo "Validation complete"

  # Cursor commit on top of which all formatted commits will be stacked
  local PREVIOUS_FORMATTED_COMMIT=$COMMIT_AFTER_FORMAT

  local COMMITS=`git rev-list --reverse HEAD ^$COMMIT_BEFORE_FORMAT`
  for COMMIT in $COMMITS; do
    echo "  Checking out commit $COMMIT"
    git checkout --quiet $COMMIT

    local FILES_DELETED=()
    local FILES_CHANGED=`git diff HEAD~ --name-only`
    for FILE in $FILES_CHANGED; do
      if test -f "$FILE"; then
        if echo "$FILE" | grep -E "\.(cpp|cc|hpp|c|h)$" > /dev/null 2>&1; then
          echo "    Formatting $FILE"
          clang-format-9 -style=file -i "$FILE"

          # NOTE: I'm not sure why but we need to run formatting twice to ensure there will be no changes when automation
          # ends up checking the commit generated to validate that there are no formatting issues. The area specifically
          # where I encountered such an issue is in include_core/omrport.h near `BOOLEAN(*sysinfo_env_iterator_hasNext)`.
          # I'm not sure if clang-format is getting confused but formatting this file after some changes it sometimes
          # introduces a space after `BOOLEAN` and formatting again a second time removes the space.
          clang-format-9 -style=file -i "$FILE"
        fi
      else
        FILES_DELETED+=("$FILE")
      fi
    done

    echo "  Committing all formatted changes"
    git commit --all --amend --no-edit --no-gpg-sign --allow-empty --quiet 2>&1

    # Save the current formatted commit for rebase on top of the previous formatted commit
    local CURRENT_FORMATTED_COMMIT=`git rev-parse HEAD`

    echo "  Checking out commit $PREVIOUS_FORMATTED_COMMIT for rebase"
    git checkout --quiet $PREVIOUS_FORMATTED_COMMIT

    FILES_CHANGED=`git diff $CURRENT_FORMATTED_COMMIT~..$CURRENT_FORMATTED_COMMIT --name-only`
    for FILE in $FILES_CHANGED; do
      local FILE_WAS_DELETED=false
      for FILE_DELETED in $FILES_DELETED; do
        if [ "$FILE" = "$FILE_DELETED" ]; then
          FILE_WAS_DELETED=true
        fi
      done

      if [ "$FILE_WAS_DELETED" = true ] ; then
        echo "    Deleting file $FILE"
        git rm --quiet --ignore-unmatch "$FILE"
      else
        echo "    Creating formatted file $FILE"
        git show $CURRENT_FORMATTED_COMMIT:"$FILE" > "$FILE"

        echo "    Adding formatted file $FILE to git repository"
        git add "$FILE"
      fi
    done

    echo "  Creating new commit with formatted files"
    git commit --reuse-message=$CURRENT_FORMATTED_COMMIT --no-gpg-sign --allow-empty --quiet 2>&1

    PREVIOUS_FORMATTED_COMMIT=`git rev-parse HEAD`

    echo "  Formatting done on commit $COMMIT"
    echo
  done

  echo "Creating a new formatted branch $NEW_BRANCH"
  git checkout --quiet -b "$NEW_BRANCH"

  echo
  echo "Formatting complete"
  echo "Old branch $OLD_BRANCH has been left unchanged"
  echo "New branch $NEW_BRANCH has been been created"
}

set_commit_status () {
  local COMMIT=""
  if [ "$TRAVIS_PULL_REQUEST_SHA" != "" ]; then
    COMMIT=$TRAVIS_PULL_REQUEST_SHA
  else
    COMMIT=$TRAVIS_COMMIT
  fi
  
  curl -k -H "Authorization: token $GITHUB_PAT" --request POST --data "{\"state\": \"$1\", \"description\": \"$2\", \"target_url\": \"$TRAVIS_BUILD_WEB_URL\", \"context\": \"continuous-integration/travis-ci/clang-format\"}" https://api.github.com/repos/fjeremic/omr-clang-format-automation/statuses/$COMMIT > /dev/null 2>&1
}

case "$1" in
  --check-against)
    if [ -z $2 ]; then
      echo "Error: --check-against expects a git <ref>" >&2
      print_help
      exit 1
    fi

    check_format "$2"
    exit 0
    ;;
  --reformat-branch)
    if [ -z $2 ] && [[ -z $3 ]]; then
      echo "Error: --reformat-branch expects two git <ref>" >&2
      print_help
      exit 1
    fi

    reformat_branch "$2" "$3"
    exit 0
    ;;
  --set-commit-status)
    if [ -z $2 ]; then
      echo "Error: --set-commit-status expects the status which can be one of error, failure, pending, or success followed by a description" >&2
      print_help
      exit 1
    fi

    set_commit_status "$2" "$3"
    exit 0
    ;;
  -*|--*=)
    echo "Error: Unsupported flag $1" >&2
    exit 1
    ;;
  *)
    print_help
    exit 1
    ;;
esac
