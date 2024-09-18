#include "testlib.h"

const char *token = "shixian_yige_zhan";
int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);

  auto case_type = ans.readInt();
  auto case_size = ans.readInt();
  auto checker_token = ouf.readString();
  auto checker_output = ouf.readString();

  if (checker_token != token) {
    quitf(_wa, "WA: grader failed");
  }

  if (checker_output == "pass") {
    quitf(_ok, "AC: size=%d, type=%d(1-stack, 2-queue, 0-hash_table)",
          case_size, case_type);
  } else {
    quitf(_wa, "WA: size=%d, type=%d(1-stack, 2-queue, 0-hash_table)",
          case_size, case_type);
  }
  return 0;
}
