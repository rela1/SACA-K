g++ -fomit-frame-pointer -W -Wall -Winline -DNDEBUG -O3 *.cpp -o saca_k.out
cd original_implementation
g++ -fomit-frame-pointer -W -Wall -Winline -DNDEBUG -O3 *.cpp -o saca_k.out
cd ..

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

for file in test_data/*.in
do
	./saca_k.out "$file" "$file.out" > "$file.stat"
	./original_implementation/saca_k.out "$file" "$file.original_out" > "$file.original_stat"
	if cmp -s "$file.original_out" "$file.out"
	then
		echo -e "${GREEN} $file test passed!${NC}"
	else
		echo -e "${RED} $file test failed!${NC}"
	fi
done