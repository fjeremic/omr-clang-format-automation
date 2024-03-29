/*******************************************************************************
 * Copyright (c) 2014, 2016 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#ifndef JITBUILDER_Z_CODEGENERATORBASE_INCL
#define JITBUILDER_Z_CODEGENERATORBASE_INCL

/*
 * The following #define and typedef must appear before any #includes in this file
 */
#ifndef JITBUILDER_CODEGENERATORBASE_CONNECTOR
#define JITBUILDER_CODEGENERATORBASE_CONNECTOR

namespace JitBuilder {
namespace Z {
class CodeGenerator;
}
} // namespace JitBuilder
namespace JitBuilder {
typedef Z::CodeGenerator CodeGeneratorConnector;
}

#else
#error JitBuilder::Z::CodeGenerator expected to be a primary connector, but a JitBuilder connector is already defined
#endif

#include "jitbuilder/codegen/JBCodeGenerator.hpp"
#include "codegen/LinkageConventionsEnum.hpp"

namespace JitBuilder {
namespace Z {

class OMR_EXTENSIBLE CodeGenerator : public JitBuilder::CodeGenerator {
public:
    CodeGenerator();
};

} // namespace Z
} // namespace JitBuilder

#endif // !defined(JITBUILDER_Z_CODEGENERATORBASE_INCL)
