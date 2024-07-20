.PHONY: FORCE
all: FORCE
	$(MAKE) -C .. quiquitocoin_qt test_quiquitocoin_qt
clean: FORCE
	$(MAKE) -C .. quiquitocoin_qt_clean test_quiquitocoin_qt_clean
check: FORCE
	$(MAKE) -C .. test_quiquitocoin_qt_check
quiquitocoin-qt quiquitocoin-qt.exe: FORCE
	 $(MAKE) -C .. quiquitocoin_qt
apk: FORCE
	$(MAKE) -C .. quiquitocoin_qt_apk
