using Random

function writefile(array, filename; base_dir = joinpath(@__DIR__,"data"))
    open(joinpath(base_dir, filename), "a+") do io
        for arr in array
            write(io, arr)
            write(io, "\n")
        end
    end;
end



function gcd_data()
    for i in 1:10000
        a = rand(1:10000)
        b = rand(1:10000)
        GCD = gcd(a,b)
        writefile(["$a $b $GCD"], "gcd.txt")
    end
end

gcd_data()