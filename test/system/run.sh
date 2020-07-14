#!/bin/bash

TIPC=../../build/src/tipc
RTLIB=../../rtlib

numtests=0
numfailures=0

curdir="$(basename `pwd`)"
if [ "${curdir}" != "system" ]; then
  echo "Test runner must be executed in .../tipc/test/system"
  exit 1
fi

# Self contained test cases
for i in selftests/*.tip
do
  base="$(basename $i .tip)"
  ((numtests++))

  ${TIPC} $i
  clang-10 -w -static $i.bc ${RTLIB}/tip_rtlib.bc -o $base

  ./${base} >/dev/null 2>/dev/null
  exit_code=${?}
  if [ ${exit_code} -ne 0 ]; then
    echo -n "Test failure for : " 
    echo $i
    ./${base}
    ((numfailures++))
  else 
    rm ${base}
  fi 
  rm $i.bc
done

for i in selftests/*.tip
do
  base="$(basename $i .tip)"
  ((numtests++))

  ${TIPC} -d $i
  clang-10 -w -static $i.bc ${RTLIB}/tip_rtlib.bc -o $base

  ./${base} >/dev/null 2>/dev/null
  exit_code=${?}
  if [ ${exit_code} -ne 0 ]; then
    echo -n "Test failure for unoptimized : "
    echo $i
    ./${base}
    ((numfailures++))
  else
    rm ${base}
  fi
  rm $i.bc
done

# IO related test cases
for i in iotests/fib-*.expected
do
  expected="$(basename $i .tip)"
  executable="$(echo $expected | cut -f1 -d-)"
  input="$(echo $expected | cut -f2 -d- | cut -f1 -d.)"
  ((numtests++))

  ${TIPC} -d iotests/$executable.tip
  clang-10 -w -static iotests/$executable.tip.bc ${RTLIB}/tip_rtlib.bc -o $executable

  ./${executable} $input >iotests/$executable.output

  diff iotests/$executable.output $i >iotests/$expected.diff

  if [[ -s /tmp/$base.diff ]]
  then
    echo -n "Test differences for : " 
    echo $i
    cat $expected.diff
    ((numfailures++))
  fi 

  rm iotests/$executable.tip.bc
  rm iotests/$executable.output
  rm iotests/$expected.diff
  rm $executable
done


if [ ${numfailures} -eq "0" ]; then
  echo "pass"
else
  echo -n "fail : "
  echo -n ${numfailures}/${numtests}
  echo " tests failed"
fi
