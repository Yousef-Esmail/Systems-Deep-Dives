#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>

/*
 * Verify the values used by ftok() to generate a System V IPC key.
 *
 * Usage:
 *   ./ftok_verify <pathname> <single-character-proj_id>
 *
 * Example:
 *   ./ftok_verify /tmp/example A
 */

int main(int argc, char *argv[]) {
  // argv[1] identifies the file; argv[2] supplies the project identifier.
  if (argc != 3 || argv[2][0] == '\0' || argv[2][1] != '\0') {
    fprintf(stderr, "Usage: %s <pathname> <single-character-proj_id>\n",
            argv[0]);
    return EXIT_FAILURE;
  }

  const char *pathname = argv[1];
  const int proj_id = (unsigned char)argv[2][0];

  /*
   * stat() fills struct stat with metadata about the file. The i-node is the
   * filesystem's identifier for the file, while st_dev identifies the device
   * containing it.
   */
  struct stat sb;

  if (stat(pathname, &sb) == -1) {
    perror("stat");
    return EXIT_FAILURE;
  }

  /*
   * These are the values examined for this exercise:
   * - st_ino: the file's i-node number.
   * - minor(st_dev): the minor device number.
   * - proj_id: the project identifier passed to ftok().
   */
  const ino_t inode = sb.st_ino;
  const unsigned int minor_dev = (unsigned int)minor(sb.st_dev);

  /*
   * ftok() combines the pathname's file information with proj_id and returns
   * the System V IPC key. It returns (key_t)-1 when key generation fails.
   */
  key_t key = ftok(pathname, proj_id);
  if (key == (key_t)-1) {
    perror("ftok");
    return EXIT_FAILURE;
  }

  // Hexadecimal output makes the values and their byte composition easier to
  // compare.
  printf("----------------------------------------\n");
  printf("File Path     : %s\n", pathname);
  printf("Project ID    : 0x%02x\n", proj_id);
  printf("Minor Device  : 0x%x\n", minor_dev);
  printf("I-node Number : 0x%lx\n", (unsigned long)inode);
  printf("ftok() Return : 0x%lx\n", (unsigned long)key);
  printf("----------------------------------------\n");

  return EXIT_SUCCESS;
}