#!/usr/bin/fish
set prim_impls {prim_adjlist, prim_adjmat, prim_heap, prim_fibheap}
set test_cnt 20
g++ kruskal.cpp -o kruskal -O2
for impl in $prim_impls
    g++ $impl.cpp -o $impl -O2 -I /usr/local/boost_1_80_0
end
for i in (seq $test_cnt)
    python gen.py 1000 10000 > data.in
    echo testcase $i:
    ./kruskal < data.in > std.out
    for impl in $prim_impls
        ./$impl < data.in > $impl.out
        if not diff -s std.out $impl.out
            echo $impl.out is wrong
            read
        end
    end
end
rm kruskal $prim_impls
rm data.in std.out
for impl in $prim_impls
    rm $impl.out
end