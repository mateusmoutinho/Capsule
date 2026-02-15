# Cortex

Cortex is a C application sandbox designed for LLM-driven development ("vibecoding"). It provides a sandboxed API so developers can build **any** application in C — web servers, CLI tools, automation scripts, data processors — without touching low-level internals like HTTP parsing, memory management boilerplate, or file I/O wrappers.

All application logic lives in a single file (`app.c`) with zero `#include` directives. Everything the application needs is accessed through a function pointer table (`appdeps`), making the sandbox self-contained, portable, and easy for LLMs to reason about.

## Features

- **Full HTTP server** — Route handling, request parsing, JSON request/response, headers, query parameters, and static file serving
- **JSON API** — Complete cJSON-based JSON creation, parsing, manipulation, serialization, and file persistence
- **File I/O** — Read, write, append, copy, move, delete files and directories; recursive listing; path concatenation
- **HTTP client** — Make outbound HTTP/HTTPS requests with custom headers, methods, and bodies
- **CLI argument parsing** — Positional arguments and flag-based options out of the box
- **Embedded assets** — Compile static files (HTML, CSS, JS, images) directly into the binary
- **Multi-target builds** — Compile for Linux (static), Windows (cross-compiled), `.deb`, `.rpm`, single-file amalgamation, or hot-reload debug mode

## Quick Start

### 1. Fork This Repository

Click **"Use this template"** on GitHub, then fork the created repository. This gives you your own copy to work with.

### 2. Clone Your Fork

```bash
git clone https://github.com/your-username/your-forked-repo.git
cd your-forked-repo
```

### 3. Pass `app.c` to an LLM

Copy the contents of [app.c](app.c) and give it to an LLM (ChatGPT, Claude, etc.) with a prompt describing what you want to build. For example:

```markdown
Using this sandbox, create a URL shortener web application:

Endpoints:
- GET /: returns a simple HTML page with a form to submit a URL to be shortened.
- POST /shorten: receives a JSON object with a "url" field and returns a JSON object with a "short_url" field.
- GET /redirect/{shortid}: receives a short URL and redirects to the original URL.

Storage schema:
Store the original URLs in a directory called "urls", with this format:
urls/
  <shorten_id>.txt
  <shorten_id2>.txt
```

### 4. Build and Run

The simplest way to compile and run:

```bash
gcc main.c -o app
./app
```

The server starts on port 3000 by default. Use `--port` to change it:

```bash
./app --port 8080
```

## Build Targets

### Simple GCC Compilation

No extra tools required — just a C compiler.

**Requirements:** [GCC or Clang](#gcc-or-clang)

```bash
gcc main.c -o app
./app
```

### Amalgamation

Creates a single `.c` file containing all application code and dependencies combined, ideal for distribution or building on systems without the full source tree.

**Requirements:** [Darwin](#darwin), [GCC or Clang](#gcc-or-clang)

```bash
darwin run_blueprint --target amalgamation
```

This produces `release/Cortex.c`. Compile and run it anywhere:

```bash
gcc release/Cortex.c -o app
./app
```

### Embedded Assets

Embeds all files from the `assets/` directory into `assets.h` and `assets.c`, so static files (HTML, CSS, JS, images) are compiled directly into the binary. This target is automatically run as a dependency of other builds like amalgamation.

**Requirements:** [Darwin](#darwin)

```bash
darwin run_blueprint --target assets
```

### Static Linux Binary

Produces a fully static Linux binary using a containerized musl-based build environment. The resulting binary has no external dependencies and runs on any Linux distribution.

**Requirements:** [Darwin](#darwin), [Docker or Podman](#docker-or-podman)

```bash
darwin run_blueprint --target static_linux --provider docker
```

### Windows Executable

Cross-compiles a Windows `.exe` using a containerized MinGW toolchain.

**Requirements:** [Darwin](#darwin), [Docker or Podman](#docker-or-podman)

```bash
darwin run_blueprint --target windows --provider docker
```

### .deb Package

Creates a Debian package (`.deb`) for installation on Debian, Ubuntu, and derivatives.

**Requirements:** [Darwin](#darwin), [Docker or Podman](#docker-or-podman)

```bash
darwin run_blueprint --target deb --provider docker
```

### .rpm Package

Creates an RPM package for installation on Fedora, RHEL, CentOS, and derivatives.

**Requirements:** [Darwin](#darwin), [Docker or Podman](#docker-or-podman)

```bash
darwin run_blueprint --target rpm --provider docker
```

### Debug Mode (Hot Reload)

Runs the application with automatic hot-reload. Whenever `main.c` or `app.c` changes, the shared library is rebuilt and reloaded without restarting the server.

**Requirements:** [Darwin](#darwin), [GCC or Clang](#gcc-or-clang), [CWebStudioFirmware](#cwebstudiofirmware)

```bash
darwin run_blueprint --target debug --compiler "gcc"
```

## Architecture

Cortex follows a **two-file model**:

| File | Purpose |
|------|---------|
| `main.c` | Server infrastructure, HTTP routing, and `appdeps` wiring. Bridges the underlying libraries to the sandbox API. Not intended for direct editing. |
| `app.c` | Application sandbox. All application logic goes here. Uses no `#include` directives — all functionality is accessed through the `appdeps` struct. |

### The `appdeps` Function Pointer Table

The `appdeps` struct is the entire API surface available to `app.c`. It provides:

| Category | Capabilities |
|----------|-------------|
| **Standard I/O** | `printf`, `sprintf`, `snprintf` |
| **String operations** | `strlen`, `strcpy`, `strcat`, `strcmp`, `strncmp`, `strstr`, `strdup` |
| **Memory** | `malloc`, `calloc`, `realloc`, `free`, `memcpy`, `memset`, `memcmp` |
| **Conversion** | `atoi`, `atof` |
| **HTTP server** | Route/method access, headers, query params, body reading, response building, JSON responses, file serving |
| **JSON** | Parse, create, manipulate, serialize, save/load (cJSON-based) |
| **File I/O** | Read/write files, directory operations, recursive listing, copy, move, delete, existence checks |
| **CLI arguments** | Positional args, flag-based args with aliases |
| **HTTP client** | Outbound requests with headers, methods, bodies, redirect control |
| **Embedded assets** | Access compiled-in static files at runtime |
| **Server control** | Start additional server instances programmatically |

### Dependencies

Header-only C libraries bundled in `dependencies/`:

- **[CWebStudio](https://github.com/OUIsolutions/CWebStudio)** (v5.3.0) — HTTP server
- **[doTheWorld](https://github.com/OUIsolutions/doTheWorld)** (v11.2.0) — File I/O utilities
- **[CArgvParse](https://github.com/OUIsolutions/CArgvParse)** (v0.0.2) — CLI argument parsing
- **[BearHttpsClient](https://github.com/aspect-build/bazel-lib)** (v0.9.2) — HTTPS client

Build system: **[Darwin](https://github.com/OUIsolutions/Darwin)** (Lua-based), configured in `darwinconf.lua` with build recipes in `builds/`.


## Projects Built with Cortex

- **[VibeLog](https://github.com/VoidLayer9/VibeLog)**

## Build Requirements

### GCC or Clang

Install a C compiler for your platform:

**Debian/Ubuntu:**
```bash
sudo apt-get install build-essential
```

**macOS:**
```bash
xcode-select --install
```

For other systems, see the official installation guides:
- [GCC Installation Guide](https://gcc.gnu.org/install/)
- [Clang Installation Guide](https://clang.llvm.org/get_started.html)

### Darwin

[Darwin](https://github.com/OUIsolutions/Darwin) is the Lua-based build system used for all advanced build targets.

**Linux** (requires `curl`):
```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.20.0/darwin_linux_bin.out -o darwin.out && chmod +x darwin.out && sudo mv darwin.out /usr/local/bin/darwin
```

**macOS** (requires `curl` and `gcc`):
```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.20.0/darwin.c -o darwin.c && gcc darwin.c -o darwin.out && sudo mv darwin.out /usr/local/bin/darwin && rm darwin.c
```

Or download a precompiled binary from the [releases page](https://github.com/OUIsolutions/Darwin/releases/tag/0.20.0).

### Docker or Podman

Required for containerized build targets (static Linux, Windows, `.deb`, `.rpm`). Install either one:

- [Docker Installation Guide](https://docs.docker.com/get-docker/)
- [Podman Installation Guide](https://podman.io/getting-started/installation)

Select your container runtime by passing `--provider` to any Darwin command:

```bash
darwin run_blueprint --target static_linux --provider podman
```

### CWebStudioFirmware

Required only for the debug/hot-reload target.

**Linux/macOS** (requires `curl` and `gcc`):
```bash
curl -L https://github.com/OUIsolutions/CWebStudioFirmware/releases/download/0.7.0/CWebStudioFirmware.c -o CWebStudioFirmware.c && gcc CWebStudioFirmware.c -o CWebStudioFirmware.out && sudo mv CWebStudioFirmware.out /usr/local/bin/CWebStudioFirmware && rm CWebStudioFirmware.c
```

Or download a precompiled binary from the [releases page](https://github.com/OUIsolutions/CWebStudioFirmware/releases/tag/0.7.0).

## License

[Unlicense](LICENSE) — Public domain. Use it however you want.
