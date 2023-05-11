# Main purpose

The main purpose of the tools introduced here is to ease the development
process for the developper.

## Is it usefull ?

It will be useless for people who can do the following...

- Read code
- Format code
- Lint code/Apply every coding rules without missing something.
- Find compilation errors/Analyze code flow
- refactore code

...at the speed of 10 000 line of code per second.

If you can do this you certainly don't need those tools.
if you can't, that's a good news, cause we don't have to spend time on what a
tools can easily do for us.

It is better to spend time on what tools CAN'T do and the developer has an
added value.

## Free and for everyone

- Works with make/cmake
- Works with every C/C++ projects
- Works with cross-compilation
- No cost, you can use them on your personnal setup

## Work as you type (or save, or push)

No one want to run a script manually, and, fortunatly, nobody will have to do
it.

- Works in real time
- Unrelated to any IDE (You should still use Vim/Neovim)
- CI (or pre-commit) intergration with reports

## Compilation database

Every C/C++ project has a different organisation, use a different build system
and is compiled for specific targets.
It implies that C/C++ projets are hard to parse and understand for any tools.

What if we have a standardized way to describe a project with all appropriate
information ?

Good news: there is! it is called a compilation database and the most utilized
format is the `compilation_database.json`.

It is as simple as it could be: A list of files with all appropriate definitions
and path to find informations to compile.
It is litteraly the command passed to compile any files but structured in a
specific format.

This compilation database can then be used as input to every tool so they can
parse code and find any information needed to understand it.

### Cmake

Cmake has a specific options to output a `compilation_commands.json`.

    -DCMAKE_EXPORT_COMPILE_COMMANDS=1

At the end of compilation you you find the file at the root of your project.

### Make/Bear

If you use Make build system, it does not ouput a `compilation_commands.json` at
the end of the build. You have to use another tool called `bear`.

Download bear `sudo apt install bear`
Then run you makefile rule starting with `bear` like this `bear -- make ...`.
Make sure you build the full project, clean your project before if necessary.
When the build is complete, `bear` will output the project
`compilation_commands.json`.

It is a simple tool that EAR the compilation commands to Build your project.

## LSP

LSP means Language Server Protocol.
It is a standardize way to communicate between a client and a server.
It's used by an editor (client) and a language specific lsp server to
communicate information about code in real time.
It enables some nice features like:
https://clangd.llvm.org/features

And the best part is that it is not related to any IDE.

It is:
- Standard
- Open source
- Available for every languages

You can get the same feature with V... any IDE.


### The right LSP server

There is certainly a LSP server for any language, and there is multiple LSP
server for C/C++ projects like `ccls` and `clangd`.

They both works the same way but we will use `clangd` for our example.

Download `clangd`: `sudo apt install clangd`

The latest is the best because you get the most up to date feature and,
sometimes, more stability.

### The LSP client

The IDE must implement a LSP client to communicate with the server (ofc). The
majority of IDE have this feature.
But, there is a wide variety of plugin of different quality. User experience
with LSP will mostly depend on the selected plugin.
Fortunatly most of IDE provide plugins of good quality to handle this part.

But how the tool  will understand the project ?

This is where the `compile_commands.json` take place.
The plugin will, most likely, find this file at the root of the project and
parse it. Then it will provide the user with all features we saw earlier thank
to a perfect understanding/parsing/compilation of your project by the LSP
server.

### How the LSP server can do this ?

We won't enter details, but we can simply say that they rely on the same tools
that compiler toolchain use to compile your code. Except it does not need to
complete the full compilation process and output .o files.
`clangd` in our case is based on the `clang` compiler.
Quoted from https://clang.llvm.org/

    The Clang project provides a language front-end and tooling infrastructure
    for languages in the C language family...

### Configuration
Assuming there IS a `compile_commands.json` in the root of the project AND
`clangd` installed. The right plugin is installed to act as a Lsp client. Note
that configuration is set using those plugins. Each plugin use its
own way to pass configuration to Lsp server. Choose a plugin you are
confortable with.

#### Vim/Neovim
Because I am totally partial, we will start with Vim in the first place.
Just install the following plugins:

    " Vim lsp client
    Plug 'prabirshrestha/vim-lsp'

    " Vim lsp feature for autocomplete
    Plug 'prabirshrestha/asyncomplete-lsp.vim'
    Plug 'prabirshrestha/asyncomplete.vim'

    " Vim lsp settings to install and setup lsp easily
    Plug 'mattn/vim-lsp-settings'

If you already installed `clangd` it should work out of the box.
If you don't just enter `:LspInstall clangd`. It is the same for any LSP server.

#### Vscode
Vscode usually work out of the box.
If there is some feature missing, it is usually because there is no proper
compilation database and Vscode plugins have a partial understanding of your
project.

#### SublimText
use the following plugin:
https://github.com/sublimelsp/LSP

## ##Eclipse
TO ADD.

## Formating, linting, static analysis and security tools
### Human vs tool

    HUMAN       BAD  --------------------------------------------------------------------------------> GOOD
                FORMAT                      LINTING                 CODE ANALYSIS               SECURITY
    TOOL        GOOD <-------------------------------------------------------------------------------- BAD

### Code format

First of all, there is a lot of tool to format code. But we will focus on one
simple tool: `clang-format`.
It is a command line interface tools that take file in input and output a
formatted file.
`sudo apt install clang-format`

#### Why

Because sharing a same way to write code is a good way to make it easily
readable and maintainable by any member of the team. It look like the code has
been written by the same person. It could be annoying at first if it is not
"our way to do it" but once we get used to it, everyone benefits from it.
It is also spending 0 time to learn the code style for new comer and wasting no
time to try format it by yourself, looking for every space and line.
It save time for your reviewer who don't have to check it, and it saves time for
 people who don't have to do another loop of fix, rebase, push to correct those
 mistakes.
To put it simple: it saves A LOT of time to developper on one a the most
annoying quality check to do.

#### How to configure it ?
Create a small `.clang-format` file at the root of the
project. Put the configuration in this file. `clang-format`
will read it and format file accordingly.

An easy way to create a clang-format configuration file:

    clang-format -style=llvm -dump-config > .clang-format

Of course the best part is that you don't have to use the CLI each time and you
can benefit from it in real time.

#### Configuration

Assuming there IS a `.clang-format` file in the root of the project AND it
contains configuration options.

#### Vim/Neovim
Because I am totally partial, we will start with Vim in the first place.
Just install the following plugin:

    " Linter and static analyzer manager (very good plugin)
    Plug 'dense-analysis/ale'

If you already installed `clangd-format` it should work out of the box.

#### Vscode
In Vscode it work out of the box.

#### SublimText
In SublimText it works out of the box.

## ##Eclipse
TO ADD.

### Linter

A little disclaimer: there is confusion between linting and static analysis
tools. They both overlap in their features. Here I made a clear difference
between both for the purpose of this documentation.

First of all, there is a lot of tool to lint code (like cpplint). But we will
focus on one simple tool: `clang-tidy`.
It is a command line interface tools that take file in input and output a
formatted file.
`sudo apt install clang-tidy`

Note that this linter is package with `clangd` and can be enable simply by
adding `--clang-tidy` to the command line.

It can easily take a compilation database to analyze a whole project easily.

#### Why

Linter tools will try to enforce best coding practice in the code. Those tools
parse the code and provide usefull advices to improve code quality and
readability. Usually linters will work to:
- Improve code expressivness
    - no magic numbers
    - const keyword where needed
    - etc
- Encourage latest standarts
    - Provide tips to use some keyword
    - etc...

Same as formatting, those mistakes are annoying to track and fix and can delay
the review steps while a tool could have warn and prevent it before any review.

#### How to configure it ?
Create a small `.clang-tidy` file at the root of the
project. Put the configuration In this file. `clang-tidy` will
read it and lint the code accordingly.

An easy way to create a clang-tidy configuration:

    clang-tidy -dump-config > .clang-tidy


#### Configuration

Assuming there IS a `.clang-tidy` file in the root of the project AND a
`compilation_commands.json` at the root of the project.

#### Vim/Neovim
Because I am totally partial, we will start with Vim in the first place.
Just install the following plugin:

    " Linter and static analyzer manager (very good plugin)
    Plug 'dense-analysis/ale'

If you already installed `clangd-tidy` it should work out of the box.

#### Vscode
In Vscode it work out of the box.
But maybe there is a toggle the feature in the intellisense plugin
configuration interface.

#### SublimText
In SublimText you will have to install the following plugin.
https://github.com/SublimeLinter/SublimeLinter

#### ##Eclipse
TO ADD.

### Static Analysis

A little disclaimer: there is confusion between linting and static analysis
tools. They both overlap in their features. Here I made a clear difference
between both for the purpose of this documentation.

Note that most of static analyzing tools are not free and require a licence.
But the tool presented here, is free and with a `GNU General Public License`.

First of all, there is a lot of tool to statically analyze code. But we will
focus on one simple tool: `cppcheck`.
It is a command line interface tools that take file in input and output a
formatted file.

    `sudo apt install cppcheck`

It can easily take a compilation database to analyze a whole project easily.

#### Why

Linter tools will try to analyze the code flow without running it (that's the
`static` part). Those tools parse the code and provide usefull advices to
find runtime error. Usually static analyzer will work to:
- Avoid runtime errors
    - Infinite loop
    - Null dereference
    - etc


#### Limits

Even if those tools are really powerfull, there do not garanty that the code is
 flawless.
 There is 2 major point to keep in mind when using static analyzer:
    - They could bring false positif.
    - They don't find every errors.

It is an help to the developper but it is up to him to avoid bugs and check
false positives.

#### How to configure it ?

Use the CLI without configuration file.
Of course the best part is that we don't have to use the CLI each time and we
can benefit from it in real time.

#### Configuration

Assuming you HAVE a a `compilation_commands.json` at the root of your project.

#### Vim/Neovim
Because I am totally partial, we will start with Vim in the first place.
Just install the following plugin:

    " Linter and static analyzer manager (very good plugin)
    Plug 'dense-analysis/ale'

If you already installed `cppcheck` it should work out of the box.

#### Vscode
In Vscode you should install `c/cpp advanced lint`.

#### SublimText
In SublimText you will have to install the following plugin.
https://github.com/SublimeLinter/SublimeLinter
And install the add on for cppcheck.

#### ##Eclipse
TO ADD.

### Security check

Free and available security tools are rare. Almost all security tools are
proprietary software with fees.

The only one I heard of is flawfinder for the C language. So we will focus on
this tool.

#### Why
Security tools will try to identify code practices that lead to security issues.
Those tools should give a good insight of security flaw related to issue. \
Usually security analyzer will work to:
    - Catch memory management issues
    - Files management issues
    - etc...

#### Limits
It is mainly a super grep with a lot of false positive.
There is only a few case where it understand the code flow.
But it catch attention on security issue and link them to CWE.
It is a good tools to improve awarness and learn more about common security
issues.

#### How to configure it ?

Use the CLI without configuration file.
Of course the best part is that you don't have to use the CLI each time and you
can benefit from it in real time.

#### Vim/Neovim
Because I am totally partial, we will start with Vim in the first place.
Just install the following plugin:

    " Linter and static analyzer manager (very good plugin)
    Plug 'dense-analysis/ale'

If you already installed `cppcheck` it should work out of the box.

#### Vscode
In Vscode you should install `c/cpp advanced lint`.

#### SublimText
To ADD.

#### ##Eclipse
TO ADD.
