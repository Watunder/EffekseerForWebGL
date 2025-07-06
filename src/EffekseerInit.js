import { Context } from './js/context.js';
import { Effect } from './js/effect.js';
import { Handle } from './js/handle.js';

/**
 * @param {{}} [moduleArg] 
 * @returns {Promise<import('./Effekseer.js').EffekseerModule>}
 */
const EffekseerInit = (moduleArg = {}) => { return; }
export default EffekseerInit;
export { Context, Effect, Handle };
