ADD_SUBDIRECTORY(2DPhysics)

# Note that FindBullet requires CMake >= 2.8.4 to find Bullet >= 2.77 
# due to Bullet's header install directory location changing.
FIND_PACKAGE(Bullet)
IF(BULLET_FOUND)
    ADD_SUBDIRECTORY(3DPhysics)
ENDIF(BULLET_FOUND)

ADD_SUBDIRECTORY(UI)