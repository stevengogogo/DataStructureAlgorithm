using Test 

struct IntersectProblem
    ps
    qs
    rs
end

struct triangle
    p 
    l 
    r
end


function getTriangle(PR::IntersectProblem, i::Int)
    lowerNode = [PR.rs[i], PR.qs[i]]
    l =  minimum(lowerNode)
    r =  maximum(lowerNode)
    return triangle(PR.ps[i], l, r)
end

function CreateIntersectProblem(length::Integer)
    ps = rand( -2^20:2^20-1, length)
    qs = rand( -2^20:2^20-1, length)
    rs = rand( -2^20:2^20-1, length)

    return IntersectProblem(ps,qs,rs)
end

function isInterseted(t1::triangle, t2::triangle) :: Bool
    if (t1.p == t2.p)
        return 1
    else 
        if (t2.p < t1.p) #Swap if t2 is smaller
            tmp = t2
            t2 = t1
            t1 = tmp
        end
        
        #t1.p < t2.p
        if (t1.r >= t2.l)
            return 1
        else
            return 0
        end
    end
end

function CountIntersects(PR::IntersectProblem)
    nCross = 0

    """
    for i in 1:(length(PR.ps)-1)
        t1 = getTriangle(PR, i)
        for j in (i+1):length(PR.ps)
            t2 = getTriangle(PR,j)
            if (isInterseted(t1, t2))
                nCross += 1
            end
        end
    end
    """

    return nCross
end

# Display
function printList(io, list)
    for i in eachindex(list)
        print(io, list[i])
        if (i < length(list))
            print(io," ")
        end
    end
    print(io, "\n")
end
function PrintProbSol(io, PR::IntersectProblem, sol::Int)
    println(io, length(PR.ps))
    printList(io, PR.ps)
    printList(io, PR.qs)
    printList(io, PR.rs)

    print(io,sol)
end

"""
ARGS=[number_of_problems]
"""
function main(ARGS)
   
    

    path = ARGS[1]

    len = parse(Int64, ARGS[2])

    Nfiles = parse(Int64, ARGS[3])

    file_I = 4

    for i in 1:Nfiles

        # Find undefined name
        #while isfile(joinpath(path, "$file_I.txt"))
            #file_I += 1
        #end

        file = joinpath(path, "$file_I.txt")

        #In/out
        io = open(file, "w")

        #Create problem
        PR = CreateIntersectProblem(len)
        #Solve Problem
        i = CountIntersects(PR)
        
        # Save to file
        PrintProbSol(io, PR, i)

        #Display
        println("Create $file")
    end

    @info "Complete $(Nfiles)"
end

main(ARGS)



## Test
"""
Data from Problem.pdf
"""
function TestData()
    # Input 1
    PR1 = IntersectProblem([12, 7, -10, 12, 9],
                           [11, 5, 5, -16, 5],
                           [-2, -13, -8, 8, 10])

    PR2 = IntersectProblem([2, -3, 6, -16, 0],
                           [-7, -14, -5, 1, 6],
                           [-12, 5, 9, 13, -8])              

    PR3 = IntersectProblem([2, 14, -16, -7, 13],
                           [7, 14, 0, 7, -5],
                           [11, -12, 8, -12, -1])

    PR4_1 = IntersectProblem([-5, 15, 15, -8, -11, -5, -13, -14, 15, 10],
                             [-7, -12, -4, -13, 5, 1, 14, -16, -16, -14],
                             [2, -13, 1, 9, 9, 1, 1, 12, -15, 6])
    PR4_2 = IntersectProblem([7, -4, -7, 12, 9, -13, -11, 5, 3, 8],
                             [8, 5, 3, -4, -10, -10, 2, 2, -7, -9],
                             [-11, -1, -1, -12, 4, 13, -16, -3, -7, 4])

    @test CountIntersects(PR1) == 10
    @test CountIntersects(PR2) == 9
    @test CountIntersects(PR3) == 10
    @test CountIntersects(PR4_1) == 45
    @test CountIntersects(PR4_2) == 44

end