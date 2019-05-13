#!/usr/bin/env bash

#ALL_TESTS=`find . -type f -executable -print`
ALL_TESTS=`find . -name test_* -type f -perm +111 -print`
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
