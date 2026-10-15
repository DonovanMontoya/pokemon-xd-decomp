# GitHub Actions builds

The workflow checks Python syntax and generates build configurations for both
supported versions on every push and pull request. These checks do not compile
the game or measure matching progress.

Full builds need original game data, which is deliberately absent from Git.
TeamOrre's `ghcr.io/teamorre/xd-decomp-build:main` image is private; a fork's
`GITHUB_TOKEN` cannot access it just by requesting `packages: read`.

For a separate repository, set the Actions repository variable `BUILD_CONTAINER`
to a private GHCR image you control. Grant that repository Actions read access
to the package. The workflow authenticates using its `GITHUB_TOKEN`.
The image must provide:

- `python`, `uv`, `ninja`, Git, and the runtime dependencies of the compiler wrapper;
- `/orig/GXXE01` and `/orig/NXXJ01` containing legally obtained original inputs
  in the layout described by each version's `config.yml`;
- `/binutils` and `/compilers` containing the project's required toolchains.

Keep the image and original data private. Full builds run only on pushes and
manual dispatches, never on pull requests. Only push trusted code to branches
in a repository with this image enabled. Without `BUILD_CONTAINER`, repositories
other than TeamOrre skip full builds and explicitly report the limitation in the
configuration job summary. A passing configuration check is not a matching build.

Successful full builds upload versioned map artifacts and
`GXXE01_report` / `NXXJ01_report`, each containing `report.json`.

## Progress tracking

As of October 15, 2026, [decomp.dev](https://decomp.dev/) says that adding new
projects is disabled. Existing project pages and historical data remain
supported. Producing report artifacts does not register a separate repository
on the site; upstream badges describe the upstream project, not a fork.
