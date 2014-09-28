program teste5 (input, output);
var i,j,k :  integer;
    a,b : boolean;
begin    
    read(i);
    j := 10;
    a := true;
    if (i < j) then
    begin
        writeln("1 if");
        if(a) then
            writeln("2 if");
        i := i + j div 2;
        if (i < j) then
        begin
            writeln("3 if");
            if(not a) then
                writeln("4 if");
            i := i + j
        end
        else
            writeln("3 else")
    end
    else
        writeln("1 else")
end.

