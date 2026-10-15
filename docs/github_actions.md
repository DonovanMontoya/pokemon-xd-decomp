# GitHub Actions builds

The workflow checks Python syntax and generates build configurations for both
supported versions on every push and pull request. These checks do not compile
the game or measure matching progress.

Full builds need original game data, which is deliberately absent from Git.
They run in a private container image that provides the data and toolchains.

Set the Actions repository variable `BUILD_CONTAINER` to a private GHCR image
you control, and grant this repository Actions read access to the package. The
workflow authenticates using its `GITHUB_TOKEN`. The image must provide:

- `python`, `uv`, `ninja`, Git, and the runtime dependencies of the compiler wrapper;
- `/orig/GXXE01` and `/orig/NXXJ01` containing legally obtained original inputs
  in the layout described by each version's `config.yml`;
- `/binutils` and `/compilers` containing the project's required toolchains.

Keep the image and original data private. Full builds run only on pushes and
manual dispatches, never on pull requests. Only push trusted code to branches
in a repository with this image enabled. Without `BUILD_CONTAINER`, full builds
are skipped and the configuration job summary says so. A passing configuration
check is not a matching build.

Successful full builds upload versioned map artifacts and
`GXXE01_report` / `NXXJ01_report`, each containing `report.json`.

## Progress tracking

Progress is tracked in this repository. The README badges are refreshed from a
local `report.json` with `tools/update_readme_progress.py`; see the README for
the commands. No external progress-tracking site is used.
