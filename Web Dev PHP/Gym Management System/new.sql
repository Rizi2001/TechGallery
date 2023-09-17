DROP TABLE members CASCADE CONSTRAINTS;
CREATE TABLE members (
  m_ID int NOT NULL PRIMARY KEY,
  m_name varchar(20) NOT NULL,
  m_password char(32) NOT NULL,
  m_age int DEFAULT NULL,
  m_gender varchar(20) DEFAULT NULL,
  m_weight float DEFAULT NULL,
  m_height decimal(3,0) DEFAULT NULL,
  m_bmi float DEFAULT NULL
);

INSERT INTO members
(m_ID,m_name,m_password,m_age,m_gender,m_weight,m_height,m_bmi)
VALUES(1000,'Mustafa','i191776',20,'Male',50,67,18);

DROP TABLE exercise CASCADE CONSTRAINTS;
CREATE TABLE exercise (
  ex_ID int NOT NULL PRIMARY KEY,
  m_ID int REFERENCES members(m_ID),
  ex_muscleGroup varchar(45) NOT NULL,
  ex_weightPlan varchar(45) NOT NULL,
  ex_equipment varchar(45) DEFAULT NULL,
  ex_name varchar(45) DEFAULT NULL,
  ex_timesADay int DEFAULT NULL,
  ex_timesAWeek int DEFAULT NULL
);

DROP SEQUENCE ex_ID;
CREATE SEQUENCE ex_ID minvalue 1 start with 1 cache 10;

INSERT INTO exercise
(ex_ID,m_ID,ex_muscleGroup,ex_weightPlan,ex_equipment,ex_name,ex_timesADay,ex_timesAWeek)
VALUES(ex_ID.nextval,1000,'Upper Body','Gain','Benchpress','xyz',2,14);

DROP TABLE nutrition CASCADE CONSTRAINTS;
CREATE TABLE nutrition (
  nu_ID int NOT NULL PRIMARY KEY,
  m_ID int REFERENCES members(m_ID),
  nu_dailyTarget int NOT NULL,
  nu_breakfast int NOT NULL,
  nu_lunch int NOT NULL,
  nu_dinner int NOT NULL
);

DROP SEQUENCE nu_ID;
CREATE SEQUENCE nu_ID minvalue 1 start with 1 cache 10;

INSERT INTO nutrition
(nu_ID,m_ID,nu_dailyTarget,nu_breakfast,nu_lunch,nu_dinner)
VALUES(nu_ID.nextval,1000,3000,1500,1000,500);


DROP TABLE log CASCADE CONSTRAINTS;
CREATE TABLE log (
  log_id int NOT NULL PRIMARY KEY,
  ex_ID int REFERENCES exercise(ex_ID),
  nu_ID int REFERENCES nutrition(nu_ID),
  log_equipment varchar(45) NOT NULL,
  log_exName varchar(45) NOT NULL,
  log_timesADay int NOT NULL,
  log_timesAWeek int NOT NULL,
  log_breakFast int NOT NULL,
  log_lunch int NOT NULL,
  log_dinner int NOT NULL
);

DROP SEQUENCE log_ID;
CREATE SEQUENCE log_ID minvalue 1 start with 1 cache 10;

SELECT * FROM members;
SELECT * FROM exercise;
SELECT * FROM nutrition;