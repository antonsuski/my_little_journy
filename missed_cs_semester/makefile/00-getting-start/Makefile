# Basics of makefile
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

# Clean
# Usualy in makefiles you can see <clean> target. It needs for cleaning files after make
# execution. For this you should run 'make clean' in terminal.
# Note: ther is user defined target the 'make' by it self don't have <clean> command.
# In this case <clean> target isn't dependency of any target in this make therefore it will
# never called implicitly. For cleaning you have to call target explicitly like this:
# 'make clean'. Be aware, we assumed that the <clean> target is not a file. And if in your
# file system file with name "clean" will be exists the target will never execute.
# It will discuss later with .phony for how to fix it.
clean:
	rm -f some_file other_file

# Variables
# Makefiles can use variables, all variables are strings. Ther is no matter in single or
# double qoutes. But it make sense in shell or bash.
# For assigning you can use '=' and ':='.
# For access to contetn in variable use either'${var}' or $(var), '$var' also works but not
# recomended.

#Example
var1 = file
var2 := file1 file2 #var2 is set of strings "file1 file2"
var3 = 'file1 file2' #it's not recomendet var3 now contain set of string "'file1 file2'"
x := file3

all:
	printf '${var1}\n'
	printf $(var2)\n
	printf $var3\n
	printf $x
