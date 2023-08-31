# All targets
# If you want to run all targets just make target <all>
# which will depend of all targets in make, like this:

# Example

all: tar1 tar2 tar3

tar1:
	echo "first target"
tar2:
	echo "second target"
tar3:
	echo "third target"

# Multiple targets.
# For multiple target for a rule use '$@' it will be runnign for
# each target

mul_tar: tar4 tar5

tar4 tar5:
	echo $@