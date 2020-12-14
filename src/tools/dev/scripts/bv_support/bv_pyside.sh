function bv_pyside_initialize
{
    export DO_PYSIDE="no"
    export USE_SYSTEM_PYSIDE="no"
    add_extra_commandline_args "pyside" "alt-pyside-dir" 1 "Use alternative directory for pyside"
}

function bv_pyside_enable
{
    DO_PYSIDE="yes"
}

function bv_pyside_disable
{
    DO_PYSIDE="no"
}

function bv_pyside_alt_pyside_dir
{
    bv_pyside_enable 
    USE_SYSTEM_PYSIDE="yes"
    PYSIDE_INSTALL_DIR="$1"
    info "using alternative pyside directory: $PYSIDE_INSTALL_DIR" 
}

function bv_pyside_depends_on
{
    pdepends=""
    if [[ "$USE_SYSTEM_PYSIDE" == "no" ]]; then
        pdepends="cmake python qt"
        # if CLANG_INSTALL_DIR not set in env, then build it
        if test -n $CLANG_INSTALL_DIR ; then
            pdepends="${pdepends} clang" 
        fi
    fi
    #info "pyside depends on ${pdepends}"
    echo ${pdepends}
}

function bv_pyside_initialize_vars
{
    info "initialize PySide vars"
}

function bv_pyside_info
{
    export PYSIDE_VERSION=${PYSIDE_VERSION:-"5.14.2"}
    export PYSIDE_FILE=${PYSIDE_FILE:-"pyside-setup-5.14.2.tar.gz"}
    export PYSIDE_BUILD_DIR=${PYSIDE_BUILD_DIR:-"pyside-setup-5.14.2"}
    #export PYSIDE_MD5_CHECKSUM="e3916fe9ffa0887c01bb0e22f78a559a"
    #export PYSIDE_SHA256_CHECKSUM="9479bc5d0bc1dc7eecdf474701ac8540a6c833cdad81fa22adecda1ff790d9bf"
}

function bv_pyside_print
{
    printf "%s%s\n" "PYSIDE_FILE=" "${PYSIDE_FILE}"
    printf "%s%s\n" "PYSIDE_VERSION=" "${PYSIDE_VERSION}"
    printf "%s%s\n" "PYSIDE_PLATFORM=" "${PYSIDE_PLATFORM}"
    printf "%s%s\n" "PYSIDE_BUILD_DIR=" "${PYSIDE_BUILD_DIR}"
}

function bv_pyside_print_usage
{
    printf "%-20s %s [%s]\n" "--pyside" "Build PySide" "$DO_PYSIDE"
    if [[ "$DO_STATIC_BUILD" == "no" ]]; then
        printf "%-20s %s [%s]\n" "--alt-pyside-dir" "Use PySide from an alternative directory"
        printf "%-20s %s [%s]\n" "--pyside-stand-alone" "Build stand-alone version of PySide."
    fi
}

function bv_pyside_host_profile
{
    if [[ "$DO_PYSIDE" == "yes" ]] ; then
        echo >> $HOSTCONF
        echo "##" >> $HOSTCONF
        echo "## PySide" >> $HOSTCONF
        echo "##" >> $HOSTCONF
        if [[ "$USE_SYSTEM_PYSIDE" == "yes"  ]] ; then
            echo "VISIT_OPTION_DEFAULT(VISIT_PYSIDE_DIR $PYSIDE_INSTALL_DIR)" >> $HOSTCONF
        else
            echo "VISIT_OPTION_DEFAULT(VISIT_PYSIDE_DIR \${VISITHOME}/pyside/$PYSIDE_VERSION/\${VISITARCH})" >> $HOSTCONF
        fi
    fi
}

function bv_pyside_ensure
{
    if [[ "$DO_PYSIDE" = "yes" && "$DO_SERVER_COMPONENTS_ONLY" == "no" && "$USE_SYSTEM_PYSIDE" == "no" ]] ; then
        ensure_built_or_ready "pyside"     $PYSIDE_VERSION    $PYSIDE_BUILD_DIR    $PYSIDE_FILE 
        if [[ $? != 0 ]] ; then
            ANY_ERRORS="yes"
            DO_PYSIDE="no"
            error "Unable to build PySide.  ${PYSIDE_FILE} not found."
        fi
    fi
}

function bv_pyside_dry_run
{
    if [[ "$DO_PYSIDE" == "yes" ]] ; then
        echo "Dry run option not set for pyside."
    fi
}

# *************************************************************************** #
#   Function 4.2, build_pyside
# *************************************************************************** #

function apply_pyside_5142_patch
{
    info "Patching Pyside2 5.14.2"
    patch -p0 << \EOF
diff -c sources/pyside2/PySide2/QtQml/CMakeLists.txt.orig sources/pyside2/PySide2/QtQml/CMakeLists.txt
*** sources/pyside2/PySide2/QtQml/CMakeLists.txt.orig
--- sources/pyside2/PySide2/QtQml/CMakeLists.txt
***************
*** 11,17 ****
  ${QtQml_GEN_DIR}/qqmlcomponent_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlcontext_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlerror_wrapper.cpp
! ${QtQml_GEN_DIR}/qqmldebuggingenabler_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlengine_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlexpression_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlextensioninterface_wrapper.cpp
--- 11,17 ----
  ${QtQml_GEN_DIR}/qqmlcomponent_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlcontext_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlerror_wrapper.cpp
! #${QtQml_GEN_DIR}/qqmldebuggingenabler_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlengine_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlexpression_wrapper.cpp
  ${QtQml_GEN_DIR}/qqmlextensioninterface_wrapper.cpp

EOF
    if [[ $? != 0 ]] ; then
        warn "Pyside2 patch1 failed."
        return 1
    fi

# wrap find_package(Pythonxxx) calls in if (NOT PYTHON_FOUND)
# to prevent a cmake error during VisIt's FindPySide call to find_package(Shiboken2)

    patch -p0 << \EOF
diff -c sources/shiboken2/data/shiboken_helpers.cmake.orig sources/shiboken2/data/shiboken_helpers.cmake
*** sources/shiboken2/data/shiboken_helpers.cmake.orig  Fri Dec  4 13:46:36 2020
--- sources/shiboken2/data/shiboken_helpers.cmake       Fri Dec  4 13:48:03 2020
***************
*** 314,319 ****
--- 314,322 ----


  macro(shiboken_find_required_python)
+   # Calling find_package for PythonInterp fails here after having already been called by
+   # VisIt in its own FindPython module, so don't call it unless needed.
+   if (NOT PYTHON_FOUND)
      if(${ARGC} GREATER 0)
          find_package(PythonInterp ${ARGV0} REQUIRED)
          find_package(PythonLibs ${ARGV0} REQUIRED)
***************
*** 324,329 ****
--- 327,333 ----
          find_package(PythonInterp REQUIRED)
          find_package(PythonLibs REQUIRED)
      endif()
+   endif()
      shiboken_validate_python_version()

      set(SHIBOKEN_PYTHON_INTERPRETER "${PYTHON_EXECUTABLE}")
EOF
    if [[ $? != 0 ]] ; then
        warn "Pyside2 patch2 failed."
        return 1
    fi

    return 0
}

function apply_pyside_patch
{
    if [[ ${PYSIDE_VERSION} == 5.14.2 ]] ; then
        apply_pyside_5142_patch
        if [[ $? != 0 ]] ; then
            return 1
        fi
    fi

    return 0
}

function build_pyside
{
    ##
    ## Prepare the build dir using src file.
    ##

    prepare_build_dir $PYSIDE_BUILD_DIR $PYSIDE_FILE
    untarred_pyside=$?
    ## 0, already exists, 1  untarred src, 2 error

    if [[ untarred_pyside == -1 ]] ; then
        warn "Unable to prepare PySide build directory. Giving Up!"
        return 1
    fi

    cd $PYSIDE_BUILD_DIR || error "Can't cd to PySide build dir."

    ##
    ## Apply patches
    ##

    apply_pyside_patch
    if [[ $? != 0 ]] ; then
        if [[ $untarred_pyside == 1 ]] ; then
            warn "Giving up on pyside build because the patch failed."
            return 1
        else
            warn "Patch failed, but continuing. I believe that this script\n" \
                 "tried to apply a patch to an existing directory that had\n" \
                 "already been patched ... that is, the patch is\n" \
                 "failing harmlessly on a second application."
        fi
    fi

    cd "$START_DIR"
    VISIT_PYSIDE_DIR="${VISITDIR}/pyside/${PYSIDE_VERSION}/${VISITARCH}/"

    pyside_opts=""
    # for finding qt
    pyside_opts="${pyside_opts} -DCMAKE_PREFIX_PATH:PATH=${QT_INSTALL_DIR}/lib/cmake/"

    # for finding python
    pyside_opts="${pyside_opts} -DPYTHON_EXECUTABLE:FILEPATH=${PYTHON_COMMAND}"

    # general cmake opotions
    pyside_opts="${pyside_opts} -DCMAKE_C_COMPILER:STRING=${C_COMPILER}"
    pyside_opts="${pyside_opts} -DCMAKE_CXX_COMPILER:STRING=${CXX_COMPILER}"
    pyside_opts="${pyside_opts} -DCMAKE_C_FLAGS:STRING=\"${CFLAGS} ${C_OPT_FLAGS}\""
    pyside_opts="${pyside_opts} -DCMAKE_CXX_FLAGS:STRING=\"${CXXFLAGS} ${CXX_OPT_FLAGS}\""
    pyside_opts="${pyside_opts} -DCMAKE_SKIP_BUILD_RPATH:BOOL=false"
    pyside_opts="${pyside_opts} -DCMAKE_BUILD_WITH_INSTALL_RPATH:BOOL=false"
    pyside_opts="${pyside_opts} -DCMAKE_INSTALL_RPATH_USE_LINK_PATH:BOOL=true"
    pyside_opts="${pyside_opts} -DCMAKE_BUILD_TYPE:STRING=\"${VISIT_BUILD_MODE}\""

    # pyside opotions
    pyside_opts="${pyside_opts} -DBUILD_TESTS:BOOL=FALSE"
    pyside_opts="${pyside_opts} -DCMAKE_INSTALL_PREFIX:PATH=\"$VISIT_PYSIDE_DIR\""
    pyside_opts="${pyside_opts} -DCMAKE_INSTALL_RPATH:FILEPATH=\"$VISIT_PYSIDE_DIR/lib\""
    pyside_opts="${pyside_opts} -DCMAKE_INSTALL_NAME_DIR:FILEPATH=\"$VISIT_PYSIDE_DIR/lib\""

    if [[ "$DO_MESAGL" == "yes" ]] ; then
        pyside_opts="${pyside_opts} -DGL_H=${MESAGL_INCLUDE_DIR}/GL/gl.h"
    fi

    CMAKE_BIN="${CMAKE_INSTALL}/cmake"

    PYSIDE_SRC_DIR=$PYSIDE_BUILD_DIR
    PYSIDE_BUILD_DIR="${PYSIDE_SRC_DIR}-build"
    if [[ ! -d $PYSIDE_BUILD_DIR ]] ; then
        echo "Making build directory $PYSIDE_BUILD_DIR"
        mkdir $PYSIDE_BUILD_DIR
    fi

    info "pyside build dir ${PYSIDE_BUILD_DIR}"

    cd "${PYSIDE_BUILD_DIR}"

    if test -e bv_run_cmake.sh ; then
        rm -f bv_run_cmake.sh
    fi

    info "Configuring pyside . . ."

    pysideenv=""
    if [[ "$DO_LLVM" == "yes" ]] ; then
        pysideenv="env CLANG_INSTALL_DIR=${VISIT_LLVM_DIR} LD_LIBRARY_PATH=${VISIT_LLVM_DIR}:${LLVM_LIB_DIR}:$LD_LIBRARY_PATH"
    fi
    echo ${pysideenv} "\"${CMAKE_BIN}\"" ${pyside_opts} ../${PYSIDE_SRC_DIR} > bv_run_cmake.sh
    cat bv_run_cmake.sh
    issue_command bash bv_run_cmake.sh || error "pyside configuration failed."

    info "Building pyside . . ."
    ${pysideenv} $MAKE $MAKE_OPT_FLAGS ||  error "PySide did not build correctly. Giving up."

    info "Installing pyside . . ."
    $MAKE install || error "PySide did not install correctly."

    if [[ $? != 0 ]] ; then
        return 1
    fi

    if [[ "$DO_GROUP" == "yes" ]] ; then
        chmod -R ug+w,a+rX "$VISITDIR/pyside"
        chgrp -R ${GROUP} "$VISITDIR/pyside"
    fi


    cd "$START_DIR"
    info "Done with PySide"

    return 0
}

function bv_pyside_is_enabled
{
    if [[ "$DO_SERVER_COMPONENTS_ONLY" == "yes" ]]; then
        return 0;
    fi 
    if [[ $DO_PYSIDE == "yes" ]]; then
        return 1    
    fi
    return 0
}

function bv_pyside_is_installed
{
    if [[ "$USE_SYSTEM_PYSIDE" == "yes" ]]; then 
        return 1
    fi

    VISIT_PYSIDE_DIR="${VISITDIR}/pyside/${PYSIDE_VERSION}/${VISITARCH}/"
    check_if_installed "pyside" $PYSIDE_VERSION
    if [[ $? != 0 ]] ; then
        return 0
    fi
    return 1
}

function bv_pyside_build
{
    #
    # Build PySide
    #
    cd "$START_DIR"
    if [[ "$DO_PYSIDE" == "yes" && "$DO_SERVER_COMPONENTS_ONLY" == "no" && "$USE_SYSTEM_PYSIDE" == "no" ]] ; then
        bv_pyside_is_installed #this returns 1 for true, 0 for false
        if [[ $? != 0 ]] ; then
            info "Skipping PySide build.  PySide is already installed."
        else
            info "Building PySide (~10 minutes)"
            build_pyside
            if [[ $? != 0 ]] ; then
                error "Unable to build or install PySide.  Bailing out."
            fi
            info "Done building PySide"
        fi
    fi
}
