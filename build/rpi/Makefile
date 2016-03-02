CC=g++
SRCDIR=../../src

SRCCORE = $(SRCDIR)/core/lodepng.cpp $(SRCDIR)/core/PolyBasicFileProvider.cpp $(SRCDIR)/core/PolyBezierCurve.cpp $(SRCDIR)/core/PolyBone.cpp $(SRCDIR)/core/PolyCamera.cpp $(SRCDIR)/core/PolyClient.cpp $(SRCDIR)/core/PolyColor.cpp $(SRCDIR)/core/PolyConfig.cpp $(SRCDIR)/core/PolyCore.cpp $(SRCDIR)/core/PolyCoreFileProvider.cpp $(SRCDIR)/core/PolyCoreInput.cpp $(SRCDIR)/core/PolyCoreServices.cpp $(SRCDIR)/core/PolyCubemap.cpp $(SRCDIR)/core/PolyData.cpp $(SRCDIR)/core/PolyEntity.cpp $(SRCDIR)/core/PolyEvent.cpp $(SRCDIR)/core/PolyEventDispatcher.cpp $(SRCDIR)/core/PolyEventHandler.cpp $(SRCDIR)/core/PolyFont.cpp $(SRCDIR)/core/PolyFontGlyphSheet.cpp $(SRCDIR)/core/PolyFontManager.cpp $(SRCDIR)/core/PolyGPUDrawBuffer.cpp $(SRCDIR)/core/PolyImage.cpp $(SRCDIR)/core/PolyInputEvent.cpp $(SRCDIR)/core/PolyLabel.cpp $(SRCDIR)/core/PolyLogger.cpp $(SRCDIR)/core/PolyMaterial.cpp $(SRCDIR)/core/PolyMaterialManager.cpp $(SRCDIR)/core/PolyMatrix4.cpp $(SRCDIR)/core/PolyMesh.cpp $(SRCDIR)/core/PolyObject.cpp $(SRCDIR)/core/PolyOpenGLGraphicsInterface.cpp $(SRCDIR)/core/PolyPAAudioInterface.cpp $(SRCDIR)/core/PolyParticleEmitter.cpp $(SRCDIR)/core/PolyPeer.cpp $(SRCDIR)/core/PolyPerlin.cpp $(SRCDIR)/core/PolyPhysFSFileProvider.cpp $(SRCDIR)/core/PolyQuaternion.cpp $(SRCDIR)/core/PolyQuaternionCurve.cpp $(SRCDIR)/core/PolyRay.cpp $(SRCDIR)/core/PolyRectangle.cpp $(SRCDIR)/core/PolyRenderDataArray.cpp $(SRCDIR)/core/PolyRenderer.cpp $(SRCDIR)/core/PolyResource.cpp $(SRCDIR)/core/PolyResourceManager.cpp $(SRCDIR)/core/PolyScene.cpp $(SRCDIR)/core/PolySceneEntityInstance.cpp $(SRCDIR)/core/PolySceneImage.cpp $(SRCDIR)/core/PolySceneLabel.cpp $(SRCDIR)/core/PolySceneLight.cpp $(SRCDIR)/core/PolySceneLine.cpp $(SRCDIR)/core/PolySceneManager.cpp $(SRCDIR)/core/PolySceneMesh.cpp $(SRCDIR)/core/PolyScenePrimitive.cpp $(SRCDIR)/core/PolySceneRenderTexture.cpp $(SRCDIR)/core/PolySceneSound.cpp $(SRCDIR)/core/PolySceneSprite.cpp $(SRCDIR)/core/PolyServer.cpp $(SRCDIR)/core/PolyShader.cpp $(SRCDIR)/core/PolySkeleton.cpp $(SRCDIR)/core/PolySocket.cpp $(SRCDIR)/core/PolySound.cpp $(SRCDIR)/core/PolySoundManager.cpp $(SRCDIR)/core/PolyString.cpp $(SRCDIR)/core/PolyTexture.cpp $(SRCDIR)/core/PolyThreaded.cpp $(SRCDIR)/core/PolyTimer.cpp $(SRCDIR)/core/PolyTimerManager.cpp $(SRCDIR)/core/PolyTween.cpp $(SRCDIR)/core/PolyTweenManager.cpp $(SRCDIR)/core/PolyVector2.cpp $(SRCDIR)/core/PolyVector3.cpp $(SRCDIR)/core/PolyVector4.cpp $(SRCDIR)/core/rgbe.cpp $(SRCDIR)/core/tinystr.cpp $(SRCDIR)/core/tinyxml.cpp $(SRCDIR)/core/tinyxmlerror.cpp $(SRCDIR)/core/tinyxmlparser.cpp $(SRCDIR)/core/PolyRPICore.cpp
OBJCORE=$(SRCCORE:.cpp=.o)

SRCTEMPLATE=TemplateApp/PolycodeTemplateApp.cpp TemplateApp/PolycodeTemplate.cpp
OBJTEMPLATE=$(SRCTEMPLATE:.cpp=.o)

RPICFLAGS=-I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -DUSE_EGL -DSTRICT_OPENGLES2 -DNO_OGG -DRPI_CORE
CFLAGS=$(RPICFLAGS) -I../../include

RPILDFLAGS=-L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lvchiq_arm -lpthread -lrt

LIBDIR=../../lib/linux_arm

LDFLAGS=-L$(LIBDIR) -lPolycore -lfreetype $(RPILDFLAGS)

default: setup core

setup:
	@mkdir -p $(LIBDIR)

.cpp.o:
	@echo "\033[1;32mBuilding \033[0m[\033[1;33m$<\033[0m]"
	@$(CC) $(CFLAGS) -c $< -o $@

core: $(OBJCORE)
	@echo "\033[1;32mLinking \033[0m[\033[1;33m$(LIBDIR)/libPolycore.a\033[0m]"
	@ar rcs $(LIBDIR)/libPolycore.a $(OBJCORE)

template: $(OBJTEMPLATE)
	@echo "\033[1;32mLinking \033[0m[\033[1;33mTemplateApp/PolycodeTemplate\033[0m]"
	@$(CC) -o TemplateApp/PolycodeTemplate $(OBJTEMPLATE) $(LDFLAGS)
	

clean:
	rm -f $(OBJCORE) $(LIBDIR)/libPolycore.a
