#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

#define BUILD_FOLDER "build/"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  Cmd cmd = {0};
  cmd_append(&cmd, "cl", "/nologo", "/Zi", "..\\src\\win32_handmade.cpp");
  cmd_append(&cmd, "user32.lib", "gdi32.lib");

  if (!mkdir_if_not_exists(BUILD_FOLDER)) return 1;
  if (!set_current_dir(BUILD_FOLDER))     return 1;
  if (!cmd_run_sync_and_reset(&cmd))      return 1;

  return 0;
}
