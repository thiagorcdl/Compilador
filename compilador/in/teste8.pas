program teste8 (input, output);
var i,j :  integer;
    procedure pinduca(i: integer; var k :integer);
    var a : integer;
    begin
        a := 20;
        i := i + 1;
        k := k * 3;
        writeln(a*i)
    end;
begin    
    i := 5;
    j := 10;
    pinduca(i,j);
    writeln("main\ti:",i,"\tj:",j)
end.

