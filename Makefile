.PHONY: install run static tags

all: install start_database messages

install:
	python bootstrap.py
	bin/buildout

run:
	bin/django runserver

static:
	bin/django collectstatic --noinput

tags:
	bin/ctags -v

start_database:
	mkdir var & true
	touch var/db
	bin/django syncdb

messages:
	bin/django compilemessages

clean:
	git clean -dfx
