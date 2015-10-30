create table big (
	a int unique,
	b float,
	c char(5),
	primary key (c)
);
insert into big values (1,1.1,'abcde');
create index hh on big (b);
insert into big values (2,1.1,'abcdf');


