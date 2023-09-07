rwildcard=$(sort $(wildcard $1$2)) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
app_name=bin.exe

src_dir = src
obj_dir = src
bin_dir = "."
res_dir = res

all_dirs:=$(dir $(call rwildcard, $(src_dir), */.))
includes:=$(addprefix -I, $(all_dirs))
all_cfiles:=$(call rwildcard, $(src_dir),*.c)
all_cfiles:=$(call rwildcard, $(src_dir),*.h)
all_ofiles:=$(addsuffix .o, $(basename $(notdir $(call rwildcard, $(src_dir),*.c)))) resources.o
link_flags:= -static -lversion -lcomctl32 -lws2_32 -municode -mwindows #-L "C:/Windows/System31"
# link_flags:= -static
cmp_flags:= -m64 -std=c99 -g

$(app_name): $(all_ofiles)
	gcc $^ -o $@ $(link_flags)

%.o: $(src_dir)/%.c

	gcc -c $< -o $@ $(includes) $(cmp_flags)
#build res
resources.o: $(res_dir)/resources.rc
	windres -v -J rc -i $(res_dir)/resources.rc -o resources.o

build: $(obj_dir)/resources.o $(app_name)

clean:
	rm *.o
	rm bin.exe
