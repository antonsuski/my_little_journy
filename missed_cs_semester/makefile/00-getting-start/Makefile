# basics of makefile

# <target> represent target in makefile and file in file system,
# <depepndency> is the file. The <target> depends on <dependency>
# command <echo "target step"> follows after target it will execute if target don't exists
# or we have newer target file in filesystem.

# target: dependency
# 	echo "target step"

# dependency:
# 	echo "dependency step"



some_file: other_file
	echo "This will always run, and runs second"
	touch some_file

other_file:
	echo "This will always run, and runs first"
	touch other_file
