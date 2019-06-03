#!/usr/bin/env bash

UNAME_OUT="$(uname -s)"
case "${UNAME_OUT}" in
    Linux*)     PLATFORM=Linux;;
    Darwin*)    PLATFORM=Mac;;
    CYGWIN*)    PLATFORM=Cygwin;;
    MINGW*)     PLATFORM=MinGw;;
    *)          PLATFORM="UNKNOWN:${UNAME_OUT}"
esac

echo "Running on: ${PLATFORM}"

if [[ "$PLATFORM" = "Mac" ]]; then
    ALL_TESTS=`find . -name test_* -type f -perm +111 -print`
else
    ALL_TESTS=`find . ! -name $(basename $0) -type f -executable -print`
fi


for TEST in ${ALL_TESTS}
do
    WORK_DIR=`dirname ${TEST}`
    WORK_DIR=${WORK_DIR#"./"}
    EXE=`basename ${TEST}`
    echo "Executing: ${EXE} in ${WORK_DIR}"
    pushd "${WORK_DIR}" > /dev/null
    "./${EXE}"
    result=$?
    popd > /dev/null

    if [[ !${result} -eq 0 ]]
    then
        exit ${result}
    else
        echo "All tests passed"
    fi

    printf '\n\n'
done
