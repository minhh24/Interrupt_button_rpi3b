SUMMARY = "LED toggle app"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://button_int.c"

S = "${WORKDIR}"

DEPENDS += "libgpiod"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} button_int.c -o button_int -pthread -lgpiod
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 button_int ${D}${bindir}
}