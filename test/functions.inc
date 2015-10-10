MD5_PATH=$( ( which md5 || which md5sum ) 2> /dev/null )

function __stdout() {
  cat ${stdout_file}
}

function __stdout_md5() {
  __stdout | ${MD5_PATH} | grep -o ^.... | head -n1
}

function __run() {
  ${cecho} "$@" > ${stdout_file} 2> ${stderr_file}
  status=$?
  stdout=$(cat ${stdout_file})
  stderr=$(cat ${stderr_file})
}

function oneTimeSetUp() {
  realpath="$( (which realpath || which grealpath ) 2> /dev/null)"
  if [[ -n ${realpath} ]]; then
    running_dir="$(${realpath} -- $(dirname $0))"
  else
    running_dir="$(pwd)/test"
  fi

  test_dir="$(mktemp -d -t cecho.XXX)"
  cecho="${running_dir}/../cecho"
  stdout_file="${test_dir}/stdout"
  stderr_file="${test_dir}/stderr"
}

function oneTimeTearDown() {
  rm -Rf ${test_dir}
  rm -Rf ${home_tmp}
}

function tearDown() {
  rm -Rf ${stdout_file} ${stderr_file}
}

function setUp() {
  cd ${running_dir}
}


# vim: ai ts=2 sw=2 et sts=2 ft=sh
