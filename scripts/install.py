#!/usr/bin/env python

"""
Performs a preprocessor-style pass over the C and S files in the input directory (argv[2]),
with the symbol CHAPTER set to argv[1], and outputs into dest directory (argv[3])
"""

import os, sys, glob, re, shutil

CHAPTER = int(sys.argv[1])
SRC_DIR = sys.argv[2]
DEST_DIR = sys.argv[3]

def preprocess(data):
    """Runs a C preprocessor like pass on data, collecting only lines wrapped in
       #if CHAPTER >= X. """

    stack = 0
    allow_again_at = []
    dont_print_endif_at = []

    lines = data.split('\n')
    newlines = []
    allow = True
    for l in lines:
        match = re.match(r'(#|%)if CHAPTER (\>=|==) (\d+)', l)
        if match:
            op = match.group(2)
            num = match.group(3)

            if allow:
                if (op == '>=' and CHAPTER >= int(num)) or \
                        (op == '==' and CHAPTER == int(num)):
                    allow = True
                    dont_print_endif_at.append(stack)
                else:
                    allow = False
                    allow_again_at.append(stack)

            stack += 1
            continue

        elif l.startswith('#else'):
            if allow:
                allow = False
                allow_again_at.append(stack-1)
            # Don't allow if we're nested in a non-allow block.
            elif stack-1 in allow_again_at:
                allow_again_at.remove(stack-1)
                dont_print_endif_at.append(stack-1)
                allow = True
            continue

        elif l.startswith('#if') or l.startswith('%if'):
            stack += 1

        elif l.startswith('#endif') or l.startswith('%endif'):
            stack -= 1
            if stack in allow_again_at:
                allow = True
                allow_again_at.remove(stack)
                continue
            if stack in dont_print_endif_at:
                dont_print_endif_at.remove(stack)
                continue


        if allow:
            newlines.append(l)

    return cleanup('\n'.join(newlines))

def cleanup(s):
    return re.sub(r'\n\n+', '\n\n', s)

####################################################
# SCRIPT START

try:
    os.mkdir(DEST_DIR)
except:
    shutil.rmtree(DEST_DIR)
    os.mkdir(DEST_DIR)

#print "Finding all .c, .h or .s files in %s..." % SRC_DIR
for f in glob.glob(SRC_DIR + '/*.c') + \
        glob.glob(SRC_DIR + '/*.s') + \
        glob.glob(SRC_DIR + '/*.h'):
#    print "Preprocessing %s..." % f
    with open(f, "r") as fd:
        data = fd.read()

    preprocessed = preprocess(data)
    if not re.match(r'^\s*$', preprocessed):
        with open(f.replace(SRC_DIR, DEST_DIR), "w") as fd:
            fd.write(preprocessed)

