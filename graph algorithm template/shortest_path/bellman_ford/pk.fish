#!/usr/bin/fish
set bf_impls {naive, roll, final}
set test_cnt 20
g++ spfa.cpp -o spfa -O2
for impl in $bf_impls
    g++ bf_$impl.cpp -o $impl -O2 -I /usr/local/boost_1_80_0
end
for i in (seq $test_cnt)
    python ../gen.py 1000 10000 > data.in
    echo testcase $i:
    ./spfa < data.in > std.out
    for impl in $bf_impls
        ./$impl < data.in > $impl.out
        if not diff -s std.out $impl.out
            echo $impl.out is wrong
            read
        end
    end
end
rm spfa
rm $bf_impls
rm data.in std.out
for impl in $bf_impls
    rm $impl.out
end