procedure main is

	x:Integer;	
	y:Integer;

begin 
	
	x:=0;
	y:=0;

	for x in 2 .. 5 
	LOOP
		y:= y+1;
	end LOOP;


Put('x');Put('\n');
Put(x);
Put('y');Put('\n');
Put(y);

end;


