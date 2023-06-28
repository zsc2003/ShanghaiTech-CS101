#!/usr/bin/fish
set dij_impls {naive, heap, fibheap}
set test_cnt 20
for impl in $dij_impls
    g++ dijkstra_$impl.cpp -o $impl -O2 -I /usr/local/boost_1_80_0
end
for i in (seq $test_cnt)
    python ../gen.py 1000 10000 > data.in
    echo testcase $i:
    for impl in $dij_impls
        ./$impl < data.in > $impl.out
    end
    for impl in $dij_impls[2..]
        if not diff -s $dij_impls[1].out $impl.out
            echo $dij_impls[1].out and $impl.out are different
            read
        end
    end
end
rm $dij_impls
rm data.in
for impl in $dij_impls
    rm $impl.out
end