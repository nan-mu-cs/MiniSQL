create table big  (
	a int,
	b int,
	c int,
	d int,
	e int,
	f int,
	g char (10),
	h char (10),
	i char (10),
	j float,
	primary key (a)
);

create index abig on big (a);

create index bbig on big (b);

create index cbig on big (c);

create index dbig on big (d);

create index ebig on big (e);

create index fbig on big (f);

create index gbig on big (g);

create index hbig on big (h);

create index ibig on big (i);

