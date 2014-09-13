program teste4 (input, output);
var i,j,k :  integer;
    a,b : boolean;
begin    
    b := (5 < 10) and ((true) or (5 <> 5));
    i := 0;
    while (i < 10) do
    begin
        j := i;
        while(j > 2) do
            j := j-1;
        i := i + j;
    end;
end.

