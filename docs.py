import subprocess
import os

def generate_doxygen_docs():
  doxyfile_path = "./Doxyfile"
  subprocess.run(["doxygen", doxyfile_path])

def ensure_dark_mode_toggle():
  header_html_path = "./libs/doxygen-awesome-css/doxygen-custom/header.html"
  if not os.path.exists(header_html_path):
    print(f"{header_html_path} does not exist. Maybe the doxygen-awesome-css submodule is not initialized?")
    print("Please run the following commands to initialize the submodule:")
    print("    git submodule update --init --recursive")
    return
  with open(header_html_path, "r", encoding="utf-8") as file:
    header_content = file.read()

  js_block = """
<script type="text/javascript" src="$relpath^doxygen-awesome-darkmode-toggle.js"></script>
<script type="text/javascript">
    DoxygenAwesomeDarkModeToggle.init()
</script>
</head>
"""

  if js_block not in header_content:
    header_content = header_content.replace("</head>", js_block)

    with open(header_html_path, "w", encoding="utf-8") as file:
      file.write(header_content)

if __name__ == "__main__":
  ensure_dark_mode_toggle()
  generate_doxygen_docs()
