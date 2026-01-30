import subprocess
import sys

EXTS = (".c", ".cc", ".cpp", ".h", ".hpp", ".inl")
EXCLUDE_PREFIX = ("libs/", "third_party/", "build/")

CHECK_MODE = "--check" in sys.argv


def run(cmd):
    result = subprocess.run(cmd)
    if result.returncode != 0:
        sys.exit(result.returncode)


output = subprocess.check_output(["git", "ls-files"], text=True)

files = []
for line in output.splitlines():
    if not line.endswith(EXTS):
        continue

    if line.startswith(EXCLUDE_PREFIX):
        continue

    files.append(line)

if not files:
    print("No files to format")
    sys.exit(0)

cmd = ["clang-format"]

if CHECK_MODE:
    cmd += ["--dry-run", "--Werror"]
else:
    cmd += ["-i"]

cmd += files

print("Running:", " ".join(cmd))
run(cmd)

print("Done.")
