rwildcard=$(sort $(wildcard $1$2)) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
app_name=lv.exe

src_dir = src

all_dirs:=$(dir $(call rwildcard, $(src_dir), */.))
includes:=$(addprefix -I, $(all_dirs))
all_cfiles:=$(call rwildcard, $(src_dir),*.c)
all_cfiles:=$(call rwildcard, $(src_dir),*.h)
all_ofiles:=$(addsuffix .o, $(basename $(notdir $(call rwildcard, $(src_dir),*.c))))

link_flags:= -static -lversion -lcomctl32 -lws2_32 -municode -mwindows
# link_flags:= -static
cmp_flags:= -O2 -m64 -std=c99 -g

$(app_name): $(all_ofiles)
	gcc $^ -o $@ $(link_flags)

%.o: $(src_dir)/%.c
	gcc -c $< -o $@ $(includes) $(cmp_flags)

build: $(app_name)

clean:
	rm -rf *.o *.exe
