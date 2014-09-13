program teste5 (input, output);
var i,j,k :  integer;
    a,b : boolean;
begin    
    read(i);
    j := 10;
    a := true;
    if (i < j) then
    begin
        if(a) then
            a := false;
        i := i + j;
    end
    else
        j := i + j;
    write(j * 18);
end.

