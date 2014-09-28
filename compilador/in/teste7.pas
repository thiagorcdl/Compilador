program teste7 (input, output);
var i :  integer;
    procedure pinduca();
    var a,b : integer;
        procedure zaeli();
        var a : integer;
        begin
            a := 20;
            writeln("zaeli: ",a)
        end
    begin
        a := 20;
        b := 30;
        zaeli();
        writeln("pinduca: ",a+b)
    end
begin    
    i := 5;
    writeln("main: ",i);
    pinduca()
end.

