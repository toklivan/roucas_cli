#!/bin/sh

BIN="./roucas_cli"

# Petit helper: exécute un test et vérifie si on attend succès ou échec.
run_test() {
  file="$1"
  expected="$2" # "ok" ou "fail"

  $BIN "$file" >/dev/null 2>&1
  code=$?

  if [ "$expected" = "ok" ] && [ $code -eq 0 ]; then
    echo "[OK]   $file"
    return 0
  fi

  if [ "$expected" = "fail" ] && [ $code -ne 0 ]; then
    echo "[OK]   $file (expected fail)"
    return 0
  fi

  echo "[FAIL] $file (exit=$code expected=$expected)"
  return 1
}

# Build d'abord
make -s re || exit 1

fail=0

run_test "tests/csv/ok.csv" "ok" || fail=1
run_test "tests/csv/bad_header.csv" "fail" || fail=1
run_test "tests/csv/bad_cols.csv" "fail" || fail=1
run_test "tests/csv/bad_number.csv" "fail" || fail=1
run_test "tests/csv/dup_id.csv" "fail" || fail=1

exit $fail
