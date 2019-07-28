# TabSpaces - Convert Tabs to Spaces and Spaces to Tabs

**This is no longer maintained, project has moved to: https://github.com/WestleyR/clint**

<br>

Yes thats right, this can convert spaces to tabs, and tabs to spaces!

<br>

## Install

```
git clone https://github.com/WestleyR/tabspaces
cd tabspaces/
make
sudo make install
```

<br>

## Usage

To convert tabs to spaces in this go file:

```bash
$ tabspaces hello.go
```

*Note: This will **NOT** mess up your gofmt assied from changing the tabs.*

<br>

To convert spaces to tabs in this file:

```bash
$ tabspaces -t hello.c
```

Again, this wont screw-up any formatting you have.

You can also add the `-v, --verbose` flag to be more verbose:

```bash
$ tabspaces -v hello.go 
VERBOSE: Converting tabs to 4 spaces.
Done: hello.go
VERBOSE: Total tabs replaced: 519
```

<br>
