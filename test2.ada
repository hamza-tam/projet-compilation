procedure main is

	x:Integer;	
	y:Integer;

begin 

	y:=0;

	for x in 3 .. 10 
	loop
		y:= y+1;
	end loop;

		

	Put('\n');
	Put(x);
	Put('\n');
	Put(y);

end;


