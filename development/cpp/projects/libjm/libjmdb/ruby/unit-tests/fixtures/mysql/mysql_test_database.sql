
drop database if exists jmdbMysqlTests;
create database jmdbMysqlTests;
use jmdbMysqlTests;

create table Address(
  id INTEGER primary key auto_increment,
  street varchar(255) not null,
  zipcode varchar(10) not null,
  city varchar(255) not null
);

create table Customer(
  id INTEGER primary key auto_increment,
  firstName varchar(255) not null,
  lastName varchar(255) not null,
  email varchar(255) not null,
  addresId int not null
);

create table Item(
  id INTEGER primary key auto_increment,
  name varchar(255) not null,
  price double not null,
  retailId bigint not null
);

create table PurchaseOrder(
  id INTEGER primary key auto_increment,
  customerId int not null,
  orderStatus int not null
);

create table PurchaseOrderLineItem(
  id INTEGER primary key auto_increment,
  purchaseOrderId int not null,
  itemId int not null,
  quantity int not null
);


insert into Address (street,zipcode,city) values ("Some street", "1234AB", "Somewhere");
insert into Customer (firstName, lastName, email, addresId) values ("Jonathan", "Maasland", "nochoice AT xs4all dot nl", 1);

insert into Address (street,zipcode,city) values ("Some other street", "1234AC", "Someplace");
insert into Customer (firstName, lastName, email, addresId) values ("A", "Nonymous", "", 2);

insert into Item(name,price,retailId) values ("Weeds season 1 dvd-box", 18.95, 12345);
insert into Item(name,price,retailId) values ("Weeds season 2 dvd-box", 18.95, 12346);
insert into Item(name,price,retailId) values ("Weeds season 3 dvd-box", 28.95, 12347);
insert into Item(name,price,retailId) values ("Weeds season 4 dvd-box", 38.95, 12348);
insert into Item(name,price,retailId) values ("Weeds season 5 dvd-box", 38.95, 1234567890123456789);

insert into PurchaseOrder(customerId,orderStatus) values(1,1);
insert into PurchaseOrderLineItem(purchaseOrderId,itemId,quantity) values (1,1,1);
insert into PurchaseOrderLineItem(purchaseOrderId,itemId,quantity) values (1,2,1);
insert into PurchaseOrderLineItem(purchaseOrderId,itemId,quantity) values (1,3,1);

