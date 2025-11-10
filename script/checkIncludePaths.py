#!/usr/bin/env python3
import os
import re
import sys

bad_include = re.compile(r'^#include\s+"([^"]+)"')
library_include = re.compile(r'Lodestone\.(.*)')
library_include_foreign = re.compile(r'^#include\s+\"((.*?)/.*)\"')
library_include_local = re.compile(r'^#include\s+<((.*?)/.*)>')

errors = []

for paths, dirs, files in os.walk(os.path.abspath("../projects")):
    for name in files:
        if name.endswith(('.cpp', '.h')): # why does it have to be tuple????
            p = os.path.join(paths, name)
            with open(p, 'r', encoding='utf-8') as f:
                lines = f.readlines()

            with open(p, 'w', encoding='utf-8') as f:
                for num, ln in enumerate(lines, start=1):
                    m = library_include_foreign.search(ln)
                    nm = library_include_local.search(ln)
                    mm = bad_include.search(ln)

                    if mm and not library_include.fullmatch(mm.group(1)): # check for relative paths (can we automate this without fucking up everything????)
                        errors.append(f"Relative path at {p}:{num}: {ln.strip()}")
                    else: # we do it when there's no errors otherwise the path will be changed the next time it looks at it
                        if m and f"{m.group(2).lstrip("Lodestone.")}" not in p: # check if all "Lodestone.{otherProj}" exists, replace with <Lodestone.{otherProj}>
                            n = f"#include <{m.group(1)}>\n"
                            print(f"Replacing '{ln.strip()}' with '{n.strip()}' in '{p}:{num}'")
                            ln = n

                        if nm and f"{nm.group(2).lstrip("Lodestone.")}" in p: # check if all <Lodestone.{currentProj}> exists, replace with "Lodestone.{currentProj}"
                            n = f"#include \"{nm.group(1)}\"\n"
                            print(f"Replacing '{ln.strip()}' with '{n.strip()}' in '{p}:{num}'")
                            ln = n

                    f.write(ln)

if errors:
    for v in errors:
        print(v)

    print("Please make these include paths absolute (e.g Lodestone.Level/Level.h)")
    print("If already absolute, please check that foreign includes are encased in <> instead of \"\"")
    sys.exit(0xDEADBEEF)