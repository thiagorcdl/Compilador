program teste9 (input, output);
var i,j :  integer;
    function pinduca(i: integer) : integer;
    var a : integer;
    begin
        a := 20;
        pinduca := a * i
    end
begin    
    i := 5;
    j := pinduca(i);
    writeln("main\ti:",i,"\tj:",j)
end.

