#import "ViewController.h"
#include "Game.hpp"


@interface ViewController ()
{
    OME::Context ctx;
}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;


- (void)setupGL;
- (void)tearDownGL;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];

    if (!self.context)
    {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    memset( &ctx, 0, sizeof( OME::Context ) );
  
    OME::Game::StartUp(&ctx);
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];

    if(ctx.onDestroy){
        ctx.onDestroy();
    }
}


- (void)update
{
    if(ctx.onUpdate){
        ctx.onUpdate(self.timeSinceLastUpdate);
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    ctx.width = view.drawableWidth;
    ctx.height = view.drawableHeight;
    if(ctx.onDraw){
        ctx.onDraw();
    }
}
@end
