require "object"

--Atom.getEnv() - return env
--Atom.getSymbol(env or klass, string) - return value
--Atom.call(function, ...) - return retvals
--Atom.createObj(klass, ...) -return obj
--Atom.callObjFunc(obj, obj_function, ...) -return retvals
--Atom.type(value) -- return Atom.T_FUNC ... etc.
--Atom.traversalEnv(env or klass, function(symbol, value))
--Atom.getKlass(obj) -return klass
--Atom.loadLib(libpath) - load a Atom.dll
--Atom.log(string) - log to log file


--lua���ñ���Ϊ����
--����Ϊ����
--Atom���ԭ���Ǿ���ʹ�ÿ����ķ�ʽ�ӱ��е������ݡ�
--ֻ���޷���lua����֧�ֵĲŻ������ã�һ������ǳ������á�
--�����֮�����ڴ��������±������ݶ���lua�Ǹ�������
--lua�޸ı������ݵ�Ψһ��ʽ��ɾ�����Ż򴴽��µķ��š�
Atom = {}

Atom.makeKlass = function(kv)
	if(Atom.type(kv) ~= Atom.T_KLS) then
		error("The Atom value is not a klass!")
	end
	local k = {
		__init = function(self, ...) self._ptr = Atom.createObj(kv, ...) end
	}
	Atom.traversalEnv(kv,
		function(name, value)
			if(type(value) == "userdata") then
				if(Atom.type(value) == Atom.T_OBJFUNC) then
					k[name] = function(self, ...)
						return Atom.callObjFunc(self._ptr, value, ...)
					end
				end
				--else if(Atom.type(value)--δ���
			else k[name] = value end
		end)
	return Object:derive(k)
end

Atom.makeObj = function(ov)
	if(Atom.type(ov) ~= Atom.T_OBJ) then
		error("The Atom value is not a object!")
	end
	local kv = Atom.getKlass(ov)
	local o = Atom.makeKlass(kv);
	--����¼��ǰmakeKlass�����value����һ������
	--���Klass���к���Obj������Obj�������Ǹ�Klass��Obj���ͻ᲻ͣ�ݹ顣
	--@todo ��¼ÿһ�������Environment�������ظ����롣
	o._ptr = ov;
	return o;
end

Atom.makeFunction = function(fv)
	return function(...)
		return Atom.call(fv, ...)
	end
end


Atom.S = function(symbol)
	return Atom.getSymbol(Atom.getEnv(), symbol)
end

function l(obj)
	return obj._ptr
end
