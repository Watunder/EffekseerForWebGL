/**
 * @typedef {HTMLImageElement | HTMLCanvasElement} TheImage
 */

/**
 * @typedef {{
 * alpha: boolean;
 * depth: boolean;
 * stencil: boolean;
 * antialias: boolean;
 * premultipliedAlpha: boolean;
 * preserveDrawingBuffer: boolean;
 * powerPreference: 0 | 1 | 2;
 * failIfMajorPerformanceCaveat: number;
 * majorVersion: 1 | 2;
 * minorVersion: 0;
 * enableExtensionsByDefault: boolean;
 * explicitSwapControl: boolean;
 * proxyContextToMainThread: 0 | 1 | 2;
 * renderViaOffscreenBackBuffer: boolean;
 * }} EmscriptenWebGLContextAttributes
 */

/**
 * @typedef {{
 * _loadBuffer: (path: string) => Promise<ArrayBufferLike>;
 * _drawEffectImage: (image: TheImage) => TheImage;
 * _loadEffectImage: (path: string) => TheImage | null;
 * _loadEffectCustomFile: (path: string, isRequired: boolean) => ArrayBufferLike | null;
 * _loadingEffect: import('./js/effect.js').Effect;
 * _resourcesMap: { [path: string]: ArrayBufferLike };
 * createContext: () => import('./js/context.js').Context;
 * releaseContext: (context: import('./js/context.js').Context) => void;
 * } & import('../build_wasm/types.js').MainModule} EffekseerModule
 */

/**
 * @type {EffekseerModule}
 */
const Effekseer = exports;
export default Effekseer;
