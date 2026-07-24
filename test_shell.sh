#!/bin/bash
set -e
echo "=================================================="
echo "Running Comprehensive Shell Feature Verification..."
echo "=================================================="

# 1. Test pwd built-in
output=$(echo -e "pwd\nexit" | ./myshell)
if [[ "$output" != *$(pwd)* ]]; then
  echo "❌ Claim Failed: pwd built-in"
  exit 1
fi
echo "✅ Claim Verified: pwd built-in"

# 2. Test cd and directory navigation
temp_dir="test_dir_$$"
mkdir -p "$temp_dir"
output=$(echo -e "cd $temp_dir\npwd\nexit" | ./myshell)
rmdir "$temp_dir"
if [[ "$output" != *$temp_dir* ]]; then
  echo "❌ Claim Failed: cd built-in or working directory change"
  exit 1
fi
echo "✅ Claim Verified: cd and directory navigation"

# 3. Test echo and output truncation redirection (>)
echo -e "echo 'Hello Shell Redirection' > test_out.txt\nexit" | ./myshell
if ! grep -q "Hello Shell Redirection" test_out.txt; then
  echo "❌ Claim Failed: Output redirection (>)"
  rm -f test_out.txt
  exit 1
fi
rm -f test_out.txt
echo "✅ Claim Verified: Output redirection (>)"

# 4. Test output append redirection (>>)
echo -e "echo 'Line One' > test_append.txt\necho 'Line Two' >> test_append.txt\nexit" | ./myshell
line_count=$(wc -l < test_append.txt | tr -d ' ')
if [ "$line_count" -ne 2 ]; then
  echo "❌ Claim Failed: Output append redirection (>>)"
  rm -f test_append.txt
  exit 1
fi
rm -f test_append.txt
echo "✅ Claim Verified: Output append redirection (>>)"

# 5. Test input redirection (<) and multi-stage pipelines (|)
echo "cpp_test_file_one.cpp" > test_in.txt
echo "cpp_test_file_two.cpp" >> test_in.txt
echo "other_file.txt" >> test_in.txt

output=$(echo -e "cat < test_in.txt | grep cpp | wc -l\nexit" | ./myshell)
rm -f test_in.txt
clean_output=$(echo "$output" | tr -d '[:space:]')
if [[ "$clean_output" != *"2"* ]]; then
  echo "❌ Claim Failed: Multi-stage pipelines or input redirection (<)"
  exit 1
fi
echo "✅ Claim Verified: Input redirection (<) and multi-stage pipes (|)"

# 6. Test history built-in tracking
output=$(echo -e "pwd\necho test_history\nhistory\nexit" | ./myshell)
if [[ "$output" != *"pwd"* ]] || [[ "$output" != *"echo test_history"* ]]; then
  echo "❌ Claim Failed: history built-in tracking"
  exit 1
fi
echo "✅ Claim Verified: history built-in tracking"

# 7. Test background job execution (&) and jobs built-in
output=$(echo -e "sleep 2 &\njobs\nexit" | ./myshell)
if [[ "$output" != *"Running"* ]] && [[ "$output" != *"PID"* ]]; then
  echo "❌ Claim Failed: Background jobs (&) and jobs built-in"
  exit 1
fi
echo "✅ Claim Verified: Background jobs (&) and jobs built-in"

echo "=================================================="
echo "🎉 All Project Claims Verified Successfully!"
echo "=================================================="