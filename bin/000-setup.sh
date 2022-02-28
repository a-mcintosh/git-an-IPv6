#!/bin/bash
#  ----------------------------------------------------------------
#  -- Aubrey McIntosh, Ph.D.  $Id: d12e09ebe220ded63c82627037cb131afb8478ac $
#  -- set some qmake variables
#  -- git@github.com:a-mcintosh/git-an-IPv6.git
#  ----------------------------------------------------------------

# $Id: $
######## change below ################################################
qmake -set TARGET git-an-IPv6
######## change above ################################################

qmake -set DESTPATH dev/deb/template/usr/local
qmake -set DESTDIR  dev/deb/template/usr/local/bin/
qmake -set EPOCH    -`git rev-parse --short HEAD`  
qmake -set debID    _001-004_all  
qmake -query

#  r1.target    =
#  r1.depends   =
#  r1.commands  =
#  QMAKE_EXTRA_TARGETS += r1


