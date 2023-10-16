test:
	gcc mountain.c -o mountain
	echo "********start to run mountain.exe******"
	mountain.exe
	echo "********end to run mountain.exe******"

all:
	gcc veri_cache.c -o veri_cache
	echo "********start to run veri_cache.exe******"
	veri_cache.exe
	echo "********end to run veri_cache.exe******"

	gcc veri_locality.c QPC_time_4locality.c -o veri_locality
	echo "********start to run veri_locality.exe******"
	veri_locality.exe
	echo "********end to run veri_locality.exe******"

	gcc design_locality.c design_locality.c -o design_locality
	echo "********start to run design_locality.exe******"
	design_locality.exe
	echo "********end to run design_locality.exe******"

	gcc mountain.c -o mountain
	echo "********start to run mountain.exe******"
	mountain.exe
	echo "********end to run mountain.exe******"

clean:
	del -f *.exe
