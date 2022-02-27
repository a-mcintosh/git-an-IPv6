rfc4193
================================

https://github.com/a-mcintosh/rfc4193.git

Copyright (c) 2022 Aubrey McIntosh, PhD

What does it do
----------------

Rfc4193 takes a sequence of IPv6 address snippets and concatenates them behind the fd::/8 prefix.  This produces a non routable address not unlike an rfc4193 address.  The lowercase hex characters, and the character ":" are processed as input.  Other characters are silently ignored.

Rfc4193 does not have any intelligence about prefix length, it is a simple input-to-output copy with some man-in-the-middle editing.  It does, however, refuse to emit multiple sets of "::" sections.  It should always emit a legal IPv6 address.  Any deviation from that is a reportable bug.  If the last quartet of digits would be empty, a "1" is appended.

On input, if the 1st 2 characters independently correspond to "f" and "d", they are also silently dropped.  This allows rfc4193 to be an identity operator on it's own output.  In general, I prefer software with this property.

In practice, the first snippet can be the git-commit-id, which gives a trade off of uniqueness and reproduceability.  Another snipped can be a project subnet.  Although RFC 4193 warns against using well known numbers, users of the same git have a unity of purpose that justifies this.  

License
-------

Use this program as you will.  However, be sure to include the tag "Copyright (c) 2022 Aubrey McIntosh, PhD"

Development process
-------------------

A side purpose for this release is to learn about qmake, and the production of .deb files.  I hand edited the Makefile produced by qmake, and "make dist" does produce a deb file.

You are invited to submit a pull request with additional items, such as environment variables and files that will help automate more of this process

Testing
-------

The output does not produce an end of line.  The envisioned use is in sed commands, e.g. 
 sed "s/42/`git rev-parse --short HEAD`/" dev/control  > $(DEB)/DEBIAN/control


