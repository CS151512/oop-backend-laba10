import { createApp, ref, reactive } from 'https://unpkg.com/vue@3/dist/vue.esm-browser.js'

createApp({
    setup() {
        const loading = ref(false)
        const activeTab = ref('Кольцо')

        const timeForm = reactive({ id: '', time_str: '' })
        const searchTimeId = ref('')
        const timeResult = ref(null)

        const mathForms = reactive({
            ring: { outer: '', inner: '' },
            triangle: { a: '', b: '', c: '' },
            rational: { num1: '', den1: '', num2: '', den2: '' },
            complex: { re1: '', im1: '', re2: '', im2: '' }
        })
        const mathResult = ref(null)

        const apiFetch = async (url, options = {}) => {
            try {
                const response = await fetch(url, options)
                const data = await response.json()
                if (!response.ok) throw data
                return data
            } catch (err) {
                return { error: err.error || err.message || "Ошибка соединения с сервером" }
            }
        }

        const createTime = async () => {
            loading.value = true
            const formData = new URLSearchParams()
            formData.append('time_str', timeForm.time_str)

            timeResult.value = await apiFetch('/api/time', {
                method: 'POST',
                body: formData,
                headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
            })

            if (!timeResult.value.error) {
                timeForm.time_str = ''
            }
            loading.value = false
        }

        const getTime = async () => {
            if (!searchTimeId.value) return
            timeResult.value = await apiFetch(`/api/time/${searchTimeId.value}`)
        }

        const calcMath = async (type) => {
            let url = ''
            const f = mathForms[type]

            switch (type) {
                case 'ring':
                    url = `/api/math/ring?outer=${f.outer}&inner=${f.inner}`
                    break
                case 'triangle':
                    url = `/api/math/triangle/area?a=${f.a}&b=${f.b}&c=${f.c}`
                    break
                case 'rational':
                    url = `/api/math/rational/add?num1=${f.num1}&den1=${f.den1}&num2=${f.num2}&den2=${f.den2}`
                    break
                case 'complex':
                    url = `/api/math/complex/add?re1=${f.re1}&im1=${f.im1}&re2=${f.re2}&im2=${f.im2}`
                    break
            }

            mathResult.value = await apiFetch(url)
        }

        return {
            loading, activeTab,
            timeForm, searchTimeId, timeResult,
            mathForms, mathResult,
            createTime, getTime, calcMath
        }
    }
}).mount('#app')
