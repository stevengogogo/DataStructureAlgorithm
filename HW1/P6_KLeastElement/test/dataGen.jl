using Random

function query(list, l,k,x)
    sortArr = sort(list[l:k])
    return sortArr[x]
end

function genVal()
    return rand(-10000:10000)
end

function printList(io,list)
    for i in eachindex(list)
        print(io, list[i])
        if (i< length(list))
            print(io," ")
        end
    end
    print(io, "\n")
end

function doDelete!(list)
    if (length(list) > 0)
        i = rand(1:length(list))
        deleteat!(list, i)
        println(inF, "Delete $i")
    else
        doInsert!(list) 
    end
end

function doQuery(list)
    if (length(list) > 0)
        l = rand(1:length(list))
        r = rand(l:length(list))
        k = rand(1: (r-l+1) )
        sublist = list[l:r]
        sort!(sublist)
        #Display
        println(ouF, sublist[k])
        println(inF, "Query $l $r $k")
    else 
        doInsert!(list)
    end
end

function doInsert!(list)
    i = rand(1:(length(list)+1))
    val = genVal()
    insert!(list, i, val)    
    #Display
    println(inF, "Insert $i $val")
end

function doReverse!(list)
    if (length(list) > 0)
        l = rand(1:length(list))
        r = rand(l:length(list))
        reverse!(list, l, r)
        # Display
        println(inF, "Reverse $l $r")
    else 
        doInsert!(list)
    end
end


function genCommand(n, q)
    cmd = [doDelete!, doReverse!, doInsert!, doReverse!]
    #n = 50000*rand() ÷ 1; # initial sequence
    #q = 50000*rand() ÷ 1; # number of commands
    #n = Int(floor(randexp()*n)) +1 
    #q = Int(floor(randexp()*q)) + 1
    println(inF, "$n $q")

    list = [ genVal() for i in 1:n]
    
    printList(inF,list)

    for i in 1:q
        C = convert(Integer, rand()*4 ÷1) + 1
        cmd[C](list)
    end

    #printList(arr, list)
    
end



function main(ARGS)
    arg = parse.(Int64, ARGS[1:2])

    inFileName = ARGS[3]
    outFileName = ARGS[4]
    #resDataF = ARGS[5]

    global inF = open(inFileName, "w")
    global ouF = open(outFileName, "w")
    #global arr = open(resDataF, "w")
    genCommand(arg[1], arg[2])

    close.([inF, ouF])
end

main(ARGS)
